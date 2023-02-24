#include "EnemyBulletBase.h"
#include "Define.h"
#include "CameraWork.h"


//-----------------------------------
//��ʊO�ɏo�����ǂ���
//-----------------------------------
bool EnemyBulletBase::ScreenOut()
{
	bool ret = false; //�߂�l
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	if ((x < 0) || (SCREEN_WIDTH < x) || (y < 0) || (SCREEN_HEIGHT < y))
	{
		ret = true;
	}

	return ret;
}

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