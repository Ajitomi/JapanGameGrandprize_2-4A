#include "Element_Fall_Floor.h"
#include "../Player.h"

#define TIMER	4.0f

Element_Fall_Floor::Element_Fall_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->area = area;
	this->type = type;
	margin_area = { -18.0f,0.0f };
	this->images = images;

	
	is_flash = false;
	fall_speed = 5.0f;
	
	state = STATE::NONE;
}

Element_Fall_Floor::~Element_Fall_Floor()
{
	for (int& image : images) {
		DeleteGraph(image);
	}
}

void Element_Fall_Floor::Update(Player* player)
{

	//LoopImages(anim_images, 0.1, 9, nullptr);

	HIT_DIRECTION is_hit_dir = std::get<1>(HitPlayer(player));

	if (is_hit_dir == HIT_DIRECTION::UP && state != STATE::FALL) {
		//�A�j���[�V�����X�V
		std::function<void()> flash = [&]() {
			is_flash = !is_flash;

			if (is_flash) {
				SetImage(0);
			}
			else {
				SetImage(images.at(0));
			}
			
		};

		//�_�ł���^�C�}�[���Z�b�g
		if (state == STATE::WORKING) { LoopTimer(0.3f, &flash); };

		//�����鎞�Ԃ̔����̎��Ԃ��o�߂�����X�e�[�g��WORKING!!�ɃZ�b�g���A�_�ł�����
		if (GetElapsedTime(TIMER) >= TIMER / 2) { state = STATE::WORKING; }

		std::function<void()> fall = [&]() {

			state = STATE::FALL;
			
		};

		//�����鎞�Ԃ̃^�C�}�[���Z�b�g
		LoopTimer(TIMER, &fall);
		
	}
	//else {
	//	state = STATE::NONE;
	//}

	if (state == STATE::FALL) {

		
		SetImage(images.at(0));
		
		if (GetLocation().y < 2000) {
			SetLocation({ GetLocation().x, GetLocation().y + fall_speed });
		}
		
	}

}
