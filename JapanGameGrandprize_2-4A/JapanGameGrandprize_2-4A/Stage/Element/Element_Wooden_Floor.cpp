#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"

Element_Wooden_Floor::Element_Wooden_Floor(MapChip* mapchip, int* image) : Stage_Element_Base(mapchip, image)
{
	original_collision = mapchip->GetArea();
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
			mapchip->SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
		}
	}
	//�v���C���[���}�b�v�`�b�v�������ɍs�����猳�̓����蔻��͈͂ɖ߂�
	else if (player->GetLocation().y > mapchip->GetLocation().y) {
		mapchip->SetArea(original_collision);
	}
	//�����蔻��͈͂̃f�o�b�N�\��
	//printfDx("x:%f, y:%f\n", mapchip->GetArea().height, mapchip->GetArea().width);
}

void Element_Wooden_Floor::Draw() const
{
}
