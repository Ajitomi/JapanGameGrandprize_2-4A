#include "BULLET.h"
#include "DxLib.h"


BULLET::BULLET()
{
	bullet_x = 0.0;
	bullet_y = 0.0;
	delete_flg = false;
	efect_explosion = nullptr;
}

BULLET::BULLET(float player_x, float player_y)
{
	delete_flg = false;
	bullet_x = player_x;
	bullet_y = player_y;
	efect_explosion = nullptr;
}

void BULLET::Draw() const
{
	if (efect_explosion != nullptr)
	{
		efect_explosion->Draw();
	}
	else 
	{
		DrawBox(bullet_x, bullet_y, bullet_x + 20, bullet_y + 10, 0xff00ff, TRUE);
	}
}

void BULLET::Update()
{
	if (bullet_x < 1260)
	{
		bullet_x += 10;
	}
	else
	{
		if (efect_explosion == nullptr)
		{
			efect_explosion = new EfectExplosion(bullet_x, bullet_y);
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