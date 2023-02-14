#include "DxLib.h"
#include "EnemyBase.h"


//-----------------------------------
// HP��0���ǂ������f(0�ɂȂ�����true)
//-----------------------------------
bool EnemyBase::CheckHp()
{
	bool ret = false;
	if (hp < 0)
	{
		ret = true;
	}
	return ret;
}

//-----------------------------------
//�h���b�v�A�C�e���̐ݒ�
//-----------------------------------
ElementItem EnemyBase::DropItem(ENEMY_TYPE enemy_type, int min_drop, int max_drop)
{
	ElementItem drop;	//�h���b�v�A�C�e��

	//������
	drop.oxygen = 0;
	drop.hydrogen = 0;
	drop.nitrogen = 0;
	drop.carbon = 0;
	drop.sulfur = 0;
	drop.chlorine = 0;
	drop.uranium = 0;


	//�h���b�v�A�C�e���ݒ�
	switch (enemy_type)
	{
	case ENEMY_TYPE::NORMAL:
		break;
	case ENEMY_TYPE::FIRE:
		drop.oxygen = min_drop + GetRand(max_drop);
		drop.nitrogen = min_drop + GetRand(max_drop);
		drop.carbon = min_drop + GetRand(max_drop);
		break;
	case ENEMY_TYPE::WATER:
		drop.oxygen = min_drop + GetRand(max_drop);
		drop.hydrogen = min_drop + GetRand(max_drop);
		drop.sulfur = min_drop + GetRand(max_drop);
		drop.chlorine = min_drop + GetRand(max_drop);
		break;
	case ENEMY_TYPE::WIND:
		drop.oxygen = min_drop + GetRand(max_drop);
		drop.hydrogen = min_drop + GetRand(max_drop);
		drop.nitrogen = min_drop + GetRand(max_drop);
		break;
	case ENEMY_TYPE::SOIL:
		drop.nitrogen = min_drop + GetRand(max_drop);
		drop.carbon = min_drop + GetRand(max_drop);
		drop.sulfur = min_drop + GetRand(max_drop);
		drop.chlorine = min_drop + GetRand(max_drop);
		break;
	case ENEMY_TYPE::THUNDER:
		drop.oxygen = min_drop + GetRand(max_drop);
		drop.hydrogen = min_drop + GetRand(max_drop);
		drop.nitrogen = min_drop + GetRand(max_drop);
		drop.carbon = min_drop + GetRand(max_drop);
		drop.sulfur = min_drop + GetRand(max_drop);
		drop.chlorine = min_drop + GetRand(max_drop);
		break;
	default:
		break;
	}

	return drop;
}

//-----------------------------------
// �h���b�v�A�C�e���̎擾
//-----------------------------------
ElementItem EnemyBase::GetDropItem() const
{ 
	return drop_item; 
}

//-----------------------------------
// �G�l�~�[�̎�ނ̎擾
//-----------------------------------
ENEMY_KIND EnemyBase::GetEnemyKind() const
{
	return kind;
}

