#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"
#include "Stage_Element.h"
#include "../CameraWork.h"


Element_Wooden_Floor::Element_Wooden_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->type = type;
	this->location = location;
	this->area = area;
	this->margin_area = { -15.0f,0.0f };
	original_collision = area;

	SetImage(images.at(0));
	original_image = images.at(0);
	
}

Element_Wooden_Floor::~Element_Wooden_Floor()
{
}

void Element_Wooden_Floor::Update(Player* player)
{
	//printfDx("%f\n", GetAnimationTime());
	/*if (GetAnimationTime() > 3.5f) {
		area = { -MAP_CHIP_SIZE, -MAP_CHIP_SIZE };
		image = 0;
	}*/

	//�v���C���[����ɂ���ꍇ�A�����蔻��͈͂�0�ɂ���
	if (/*HitPlayer(player) && */player->GetLocation().y - player->GetArea().height / 2 - 4.0f < location.y) {
		//���X�e�B�b�N���������ɓ|���Ă���
		if (PAD_INPUT::GetLStick().y <= -10000)
		{
			//area = { -MAP_CHIP_SIZE, -MAP_CHIP_SIZE };
			SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
			//SetImage(0);
			
		}
		

	}


	//�v���C���[���}�b�v�`�b�v�������ɍs�����猳�̓����蔻��͈͂ɖ߂�
	else if (player->GetLocation().y - player->GetArea().height / 2 - 4.0f> location.y) {
		
		SetArea(original_collision);
		image = original_image;
	}

	//�����蔻��͈͂̃f�o�b�N�\��
	//printfDx("x:%f, y:%f\n", mapchip->GetArea().height, mapchip->GetArea().width);
}

//void Element_Wooden_Floor::Draw() const
//{
//	float x = location.x - CameraWork::GetCamera().x;
//	float y = location.y - CameraWork::GetCamera().y;
//	DrawRotaGraphF(x, y, 1.0f, 0, image, TRUE);
//}
