#include "Bullet.h"
#include "DxLib.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Bullet::Bullet()
{
	delete_flg = false;
	efect_explosion = nullptr;
}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Bullet::Bullet(float player_x, float player_y)
{
	delete_flg = false;
	efect_explosion = nullptr;
}
