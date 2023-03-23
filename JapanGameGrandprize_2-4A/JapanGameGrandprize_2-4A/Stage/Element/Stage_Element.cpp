#include "Stage_Element.h"
#include "../CameraWork.h"

//#define NODEBUG

Stage_Element::Stage_Element()
{
	player = nullptr;
}

Stage_Element::~Stage_Element()
{
	for (const auto& entry : image_cache) {
		for (auto& value : entry.second) {
			DeleteGraph(value);
		}
	}
}

void Stage_Element::AddElement(short type, Location location, Area area)
{
#ifndef NODEBUG

	
	std::vector<int> images = GetImage(type);
	/*int* images = new int[buf.size()];
	std::copy(buf.begin(), buf.end(), images);*/
	

	switch (type)
	{
	case DAMAGE_WALL:
		element.push_back(std::make_shared<Element_DamageWall>(type, element, images, location, Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE }));
		break;

	case WOODEN_FLOOR:
		element.push_back(std::make_shared <Element_Wooden_Floor>(type, element, images, location, Area{ 10.0f, MAP_CHIP_SIZE }));
		break;

	case FALL_FLOOR:
		element.push_back(std::make_shared<Element_Fall_Floor>(type, element, images, location, Area{ 10.0f , MAP_CHIP_SIZE }));
		break;

	case TRAP:
		element.push_back(std::make_shared<Element_Trap>(type, element, images, location, Area{ MAP_CHIP_SIZE , MAP_CHIP_SIZE }));
		break;

	case MOVE_FLOOR:
		element.push_back(std::make_shared<Element_Move_Floor>(type, element, images, location, area));
		break;

	case BARRICADE:
		element.push_back(std::make_shared<Element_Move_Floor>(type, element, images, location, area));
		break;

	default:
		break;
	}
#endif // !NODEBUG	
}

void Stage_Element::Update(Player* player)
{
	//�����蔻�艉�Z�͈�
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& e : element)
	{
		if (e == nullptr) continue;

		float x = e->GetLocation().x;
		float y = e->GetLocation().y;
		float w = e->GetArea().width;
		float h = e->GetArea().height;

		//�u���b�N�͈̔͂��Œ艻
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// ��ʓ��ɂ���MapChip�I�u�W�F�N�g����Update����
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;


		e->Update(player);

	}
}

void Stage_Element::Draw() const
{

	//�����蔻�艉�Z�͈�
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& e : element)
	{
		if (e == nullptr) continue;

		float x = e->GetLocation().x;
		float y = e->GetLocation().y;
		float w = e->GetArea().width;
		float h = e->GetArea().height;

		//�u���b�N�͈̔͂��Œ艻
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// ��ʓ��ɂ���MapChip�I�u�W�F�N�g����Update����
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;


		e->Draw();

	}
}

std::vector<int> Stage_Element::GetImage(short type)
{
	

	// ���łɓǂݍ��܂ꂽ�摜���L���b�V���ɂ��邩�ǂ������m�F
	if (image_cache.find(type) != image_cache.end()) {

		return image_cache[type];
	}

	// �摜���L���b�V���ɂȂ��ꍇ�A�ǂݍ��݂��s��


	std::string filename = "";

	switch (type)
	{
	case DAMAGE_WALL:
		filename = "DamageWall.png";
		break;

	case WOODEN_FLOOR:
		filename = "Wooden_Floor.png";
		break;

	case FALL_FLOOR:
		filename = "Fall_Floor.png";
		break;

	case TRAP:
		filename = "TRAP.png";
		break;

	case MOVE_FLOOR:
		filename = "Move_Floor.png";
		break;

	case BARRICADE:
		filename = "Wooden_Floor.png";
		break;

	default:
		filename = "File name not found";
		break;
	}

	// �ǂݍ��񂾉摜���L���b�V���ɕۑ�
	image_cache[type] = LoadImage(filename);

	
	return image_cache[type];


}

std::vector<int> Stage_Element::LoadImage(const std::string& filename)
{
	//�f�t�H���g�f�B���N�g��
	const std::string default_dir = "Images/Stage/Element/";

	const std::string file_dir = default_dir + filename;

	std::vector<int> images;

	int buf = LoadGraph(TEXT(file_dir.c_str()));

	int image_width, image_height;

	GetGraphSize(buf, &image_width, &image_height);

	if (image_width == MAP_CHIP_SIZE && image_height == MAP_CHIP_SIZE) {
		images.push_back(buf);
		
	}
	else {
		DeleteGraph(buf);

		int x_num = image_width / MAP_CHIP_SIZE;
		int y_num = image_height / MAP_CHIP_SIZE;
		int total_num = x_num * y_num;

		
		std::vector<int> buf_images(total_num);

		LoadDivGraph(TEXT(file_dir.c_str()), total_num, x_num, y_num, MAP_CHIP_SIZE, MAP_CHIP_SIZE, &buf_images[0]);

		//�v�f����ύX���A�R�s�[
		images.resize(total_num);
		std::copy(buf_images.begin(), buf_images.end(), images.begin());

	}


#if 0
	//�ǂݍ��݃��O
	for (int i = 0; i < images.size(); i++) {
		printfDx("[%d]ID:%d\t%s\n", i, images.at(i), TEXT(filename.c_str()));
}
#endif // 0

	

	return images;

	//return std::vector<int>();
}
