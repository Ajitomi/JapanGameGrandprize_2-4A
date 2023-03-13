#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"
#include "Stage_Element.h"


Element_Wooden_Floor::Element_Wooden_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : Stage_Element_Base(element, image, location, area)
{
	this->type = Element::DEBUG_GRASS;
	original_collision = area;
	original_image = *image;

	//*image = LoadGraph("Images/Stage/Wooden_Floor.png");
	area = { MAP_CHIP_SIZE, MAP_CHIP_SIZE };
}

Element_Wooden_Floor::~Element_Wooden_Floor()
{
}

void Element_Wooden_Floor::Update(Player* player)
{
	//�v���C���[����ɂ���ꍇ�A�����蔻��͈͂�0�ɂ���
	if (HitPlayer(player)) {
		//���X�e�B�b�N���������ɓ|���Ă���
		if (PAD_INPUT::GetLStick().y <= -10000)
		{
			area = { -MAP_CHIP_SIZE, -MAP_CHIP_SIZE };
			SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
			image = 0;
		}
	}
	//�v���C���[���}�b�v�`�b�v�������ɍs�����猳�̓����蔻��͈͂ɖ߂�
	else if (player->GetLocation().y > location.y) {
		area = original_collision;
		image = original_image;
	}

	//�����蔻��͈͂̃f�o�b�N�\��
	//printfDx("x:%f, y:%f\n", mapchip->GetArea().height, mapchip->GetArea().width);
}

void Element_Wooden_Floor::Draw() const
{

	MapChip::Draw();
}
