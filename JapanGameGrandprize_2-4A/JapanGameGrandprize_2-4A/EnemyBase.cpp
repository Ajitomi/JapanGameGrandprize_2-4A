#include "EnemyBase.h"
#include "DxLib.h"
#include "vector"
#include "CameraWork.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
EnemyBase::EnemyBase() 
{

	can_delete = false;
	left_move = true;
	poison = false;
	paralysis = false;
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
	images = nullptr;
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
//��ʊO�ɏo��
//-----------------------------------
bool EnemyBase::ScreenOut()
{

	bool ret = false; //�߂�l
	Location scroll; //��ʃX�N���[�����l���������W
	Location camera = CameraWork::GetCamera(); //�J����
	scroll = location - camera;

	if ((scroll.x < -(area.width / 2)) || (SCREEN_WIDTH + (area.width / 2) < scroll.x) ||
		(scroll.y < -(area.height / 2)) || (SCREEN_HEIGHT + (area.height / 2) < scroll.y))
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//�X�e�[�W�Ƃ̓����蔻��
//-----------------------------------
HitMapChip EnemyBase::HitStage(const Stage* stage)
{

	HitMapChip ret = { false,nullptr }; //�߂�l

	//�}�b�v�`�b�v
	std::vector<MapChip*>map_chip = stage->GetMapChip();

	//�J�����̈ʒu
	Location camera = CameraWork::GetCamera();

	for (MapChip* chip : map_chip)
	{
		if (chip != nullptr)
		{
			Location chip_location = chip->GetLocation();
			Area chip_area = chip->GetArea();

			if ((location.x - (area.width / 2) <= chip_location.x + (chip_area.width / 2)) &&
				(chip_location.x - (chip_area.width / 2) <= location.x + (area.width / 2)))
			{
				if (HitBox(chip))
				{
					ret.hit = true;
					ret.chip = chip;
					break;
				}
			}
		}
	}

	return ret;
}

//-----------------------------------
//�X�e�[�W�̂ǂ̖ʂƓ��������𔻒f
//-----------------------------------
STAGE_DIRECTION EnemyBase::HitDirection(const MapChip* map_chip)
{

	STAGE_DIRECTION ret = STAGE_DIRECTION::TOP; //�߂�l

	Location chip_location = map_chip->GetLocation();
	Area chip_area = map_chip->GetArea();
	Location vertex = location; //���_
	float distance[4]; //����
	int min_vertex; //�����������_
	float min_distance; //�Œ዗��

	//����Ƃ̋���
	distance[0] = sqrtf(powf(chip_location.x - (location.x + area.width / 2), 2) +
		powf(chip_location.y - (location.y - area.height / 2), 2));

	//�E��Ƃ̋���
	distance[1] = sqrtf(powf(chip_location.x - (location.x - area.width / 2), 2) +
		powf(chip_location.y - (location.y - area.height / 2), 2));

	//�����Ƃ̋���
	distance[2] = sqrtf(powf(chip_location.x - (location.x - area.width / 2), 2) +
		powf(chip_location.y - (location.y + area.height / 2), 2));

	//�E���Ƃ̋���
	distance[3] = sqrtf(powf(chip_location.x - (location.x + area.width / 2), 2) +
		powf(chip_location.y - (location.y + area.height / 2), 2));

	min_distance = distance[0];
	min_vertex = 0;

	for (int i = 1; i < 4; i++)
	{
		if (distance[i] < min_distance)
		{
			min_distance = distance[i];
			min_vertex = i;
		}
	}
	
	switch (min_vertex)
	{
	case 0:
		vertex = { location.x - (area.width / 4),location.y - (area.height / 4) };
		break;
	case 1:
		vertex = { location.x + (area.width / 4),location.y - (area.height / 4) };
		break;
	case 2:
		vertex = { location.x - (area.width / 4),location.y + (area.height / 4) };
		break;
	case 3:
		vertex = { location.x + (area.width / 4),location.y + (area.height / 4) };
		break;
	default:
		break;
	}

	//��ʂƂ̋���
	distance[0] = sqrtf(powf(chip_location.x - vertex.x, 2) +
		powf((chip_location.y - CHIP_SIZE / 2) - vertex.y, 2));

	//���ʂƂ̋���
	distance[1] = sqrtf(powf(chip_location.x - vertex.x, 2) +
		powf((chip_location.y + CHIP_SIZE / 2) - vertex.y, 2));

	//���ʂƂ̋���
	distance[2] = sqrtf(powf((chip_location.x - CHIP_SIZE / 2) - vertex.x, 2) +
		powf(chip_location.y - vertex.y, 2));

	//�E�ʂƂ̋���
	distance[3] = sqrtf(powf((chip_location.x + CHIP_SIZE / 2) - vertex.x, 2) +
		powf(chip_location.y - vertex.y, 2));

	min_distance = distance[0];
	for (int i = 1; i < 4; i++)
	{
		if (distance[i] < min_distance)
		{
			min_distance = distance[i];
			ret = static_cast<STAGE_DIRECTION>(i);
		}
	}

	return ret;
}

//-----------------------------------
//�ŏ�Ԃ̏���
//-----------------------------------
void EnemyBase::Poison()
{

	if (poison)
	{
		poison_time--;
		if (0 < poison_time)
		{
			if (poison_time % POISON_DAMAGE_FLAME == 0)
			{
				hp -= poison_damage;
			}
		}
		else
		{
			poison = false;
		}
	}
}

//-----------------------------------
//��჏�Ԃ̏���
//-----------------------------------
void EnemyBase::Paralysis()
{

	if (paralysis)
	{
		paralysis_time--;
		if (paralysis_time < 0)
		{
			paralysis = false;
		}
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
int EnemyBase::GetDropVolume() const
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