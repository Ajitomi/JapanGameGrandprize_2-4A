#include "DxLib.h"
#include "EnemyBase.h"
#include "Stage/Stage.h"
#include "vector"
#include "CameraWork.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
EnemyBase::EnemyBase() 
{
	can_delete = false;
	left_move = true;
	hp = 0;
	speed = 0;
	paralysis_time = 0;
	poison_damage = 0;
	poison_time = 0;
	drop_volume = 0;
	drop_type_volume = 0; 

	drop_element = nullptr;

	kind = ENEMY_KIND::NONE; 
	state = ENEMY_STATE::IDOL;
	type = nullptr;
}

//-----------------------------------
// HP��0���ǂ������f(0�ɂȂ�����true)
//-----------------------------------
bool EnemyBase::CheckHp()
{
	bool ret = false;
	if (hp <= 0)
	{
		ret = true;
	}
	return ret;
}

//-----------------------------------
//�X�e�[�W�Ƃ̓����蔻��
//-----------------------------------
bool EnemyBase::HitStage(const Stage* stage)
{
	bool ret = false; //�߂�l

	//�}�b�v�`�b�v
	std::vector<MapChip*>map_chip = stage->GetMapChip();

	//�J�����̈ʒu
	Location camera = CameraWork::GetCamera();

	//�`��͈͂̐ݒ�
	Area draw_area = { SCREEN_HEIGHT + CHIP_SIZE,SCREEN_WIDTH + CHIP_SIZE };

	for (MapChip* chip : map_chip)
	{
		if (chip != nullptr)
		{
			Location chip_location = chip->GetLocation();
			Area chip_area = chip->GetArea();

			//�`��͈͓��ɂ���u���b�N
			if ((camera.x < chip_location.x + chip_area.width) && (chip_location.x < camera.x + draw_area.width) &&
				(camera.y < chip_location.y + chip_area.height) && (chip_location.y < camera.y + draw_area.height))
			{
				if (HitBox(chip))
				{
					if (state == ENEMY_STATE::MOVE)
					{
						if ((chip_location.y + chip_area.height / 2) < (location.y + area.height / 2))
						{
							if (left_move)
							{
								location.x = (chip_location.x + (chip_area.width / 2) + (area.width / 2) + 2);
							}
							else
							{
								location.x = (chip_location.x - (chip_area.width / 2) - (area.width / 2) - 2);
							}
							left_move = !left_move;
							speed = -speed;
						}
					}
					if (state == ENEMY_STATE::FALL) //�������
					{
						location.y = (chip_location.y - (chip_area.height / 2) - (area.height / 2)) + 2;
					}

					ret = true;
					break;
				}
			}
		}
	}

	return ret;
}

//-----------------------------------
//�ŏ�Ԃ̏���
//-----------------------------------
void EnemyBase::Poison()
{
	if (0 < poison_time)
	{
		poison_time--;
		if (poison_time % POISON_DAMAGE_FLAME == 0)
		{
			hp -= poison_damage;
		}
	}
}

//-----------------------------------
//��჏�Ԃ̏���
//-----------------------------------
void EnemyBase::Paralysis()
{
	if (0 < paralysis_time)
	{
		paralysis_time--;
		speed *= 0.7;
	}
}
//-----------------------------------
//�h���b�v�����ނ̗ʂ̎擾
//-----------------------------------
int EnemyBase::GetDropTypeVolume() const
{
	return drop_type_volume;
}

//-----------------------------------
//�h���b�v����A�C�e���̗ʂ̎擾
//-----------------------------------
int EnemyBase::GetDropVolume()const
{
	return drop_volume;
}

//-----------------------------------
// �h���b�v�A�C�e���̎擾
//-----------------------------------
ElementItem EnemyBase::GetDropItem(int i) const
{ 
	return *drop_element[i]; 
}

//-----------------------------------
// �G�l�~�[�̎�ނ̎擾
//-----------------------------------
ENEMY_KIND EnemyBase::GetEnemyKind() const
{
	return kind;
}

//-----------------------------------
//�G�l�~�[�̏�Ԃ̎擾
//-----------------------------------
ENEMY_STATE EnemyBase::GetState()const
{
	return state;
}

//-----------------------------------
//�폜�\��Ԃ̎擾
//-----------------------------------
bool EnemyBase::GetCanDelete() const
{
	return can_delete;
}