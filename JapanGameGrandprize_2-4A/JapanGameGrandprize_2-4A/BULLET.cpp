#include "Bullet.h"
#include "DxLib.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Bullet::Bullet()
{
	location.x = 0.0;
	location.y = 0.0;
	delete_flg = false;
	efect_explosion = nullptr;
}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Bullet::Bullet(float player_x, float player_y)
{
	delete_flg = false;
	location.x = player_x;
	location.y = player_y;
	efect_explosion = nullptr;
}

//-----------------------------------
// �`��
//-----------------------------------
void Bullet::Draw() const
{
	if (efect_explosion != nullptr)
	{
		efect_explosion->Draw();
	}
	else 
	{
		DrawBox(location.x, location.y, location.x + 20, location.y + 10, 0xff00ff, TRUE);
	}
}

//-----------------------------------
// �X�V
//-----------------------------------
void Bullet::Update()
{
	if (location.x < 1260)
	{
		location.x += 10;
	}
	else
	{
		if (efect_explosion == nullptr)
		{
			efect_explosion = new EfectExplosion(location.x, location.y);
		}
		else
		{
			efect_explosion->Update();
		}

		if (efect_explosion->GetDeleteFlg())
		{
			delete_flg = true;
		}

	}
}