#include "Bullet.h"
#include "DxLib.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Bullet::Bullet()
{
	efect_end = false;
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

bool Bullet::GetEfectFlg()
{
	return efect_end;
}
