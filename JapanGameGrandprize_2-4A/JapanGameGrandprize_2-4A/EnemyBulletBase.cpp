#include "EnemyBulletBase.h"


//-----------------------------------
//�_���[�W�̎擾
//-----------------------------------
int EnemyBulletBase::GetDamage() const
{
	return damage;
}

//-----------------------------------
//�^�C�v�̎擾
//-----------------------------------
ENEMY_TYPE EnemyBulletBase::GetType() const
{
	return type;
}