#include "Bullet.h"
#include "DxLib.h"
#include "player.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
BulletBase::BulletBase()
{
	efect_end = false;
	delete_flg = false;
	efect_explosion = nullptr;
}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
BulletBase::BulletBase(float player_x, float player_y)
{
	delete_flg = false;
	efect_explosion = nullptr;
}

bool BulletBase::GetEfectFlg() const
{
	return efect_end;
}

float BulletBase::GetDamage() const
{
	return damage;
}

float BulletBase::GetDebuffTime() const
{
	return debuff_time;
}

ATTRIBUTE BulletBase::GetAttribute() const
{
	return attribute;
}