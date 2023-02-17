#include "DxLib.h"
#include "EnemyBase.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
EnemyBase::EnemyBase() 
{
	hp = 0;
	speed = 0;
	drop_volume = 0;
	drop_type_volume = 0; 

	drop_element = nullptr;

	kind = ENEMY_KIND::NONE; 
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
//�폜�\��Ԃ̎擾
//-----------------------------------
bool EnemyBase::GetCanDelete() const
{
	return can_delete;
}