#include "Player.h"
#include "DxLib.h"
#include "PadInput.h"
#include "CameraWork.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Player::Player()
{
	location.x = 0;
	location.y = 420;
	image = 0;
	image_size_x = 40;
	image_size_y = 80;
	bullet_count = 0;
	count = 0;
	jump = 10.0;
	jump_power = 0.0;
	not_jet_count = 0;
	speed_x = 0.0;
	fuel = 100.0;
	for (int i = 0; i < 30; i++)
	{
		bullet = new Bullet * [30];
		bullet[i] = nullptr;
	}

	stage = new Stage();

	area = { 80,40 };
	//GetGraphSize(image, &image_size_x, &image_size_y);
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Player::~Player()
{
	for (int i = 0; i < 30; i++)
	{
		//delete bullet[i];
	}
	delete[] bullet;
}

//-----------------------------------
// �`��
//-----------------------------------
void Player::Draw() const
{

	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	//DrawBox(x, y, x + image_size_x, y + image_size_y, 0x00ff00, TRUE);

	DrawBox(x - (area.width / 2), y - (area.height / 2), x - (area.width / 2) + area.width, y - (area.height / 2) + area.height, 0x00ff00, TRUE);

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}

	DrawFormatString(0, 0, 0x00ff00, "%f %f", jump_power, fuel);

	//printfDx("X%f\tY%f\n", location.x, location.y);
	//printfDx("\t\tX%f\tY%f\n", x, y);

	//DrawBoxAA(x - (area.width / 2) - 1, y - (area.height / 2) - 1, x - (area.width / 2) + area.width + 1, y - (area.height / 2) + area.height + 1, 0x000000, TRUE, 0.5F);
}

//-----------------------------------
// �X�V
//-----------------------------------
void Player::Update()
{
	//�������Ă������
	//���v����[1:��, 2:�E, 3:��, 4:��]
	short collision_dir = 0;

	for (int i = 0; i < stage->GetMapChip().size(); i++)
	{

		collision_dir = stage->GetMapChip().at(i)->GetMapChip_Collision();
		if (collision_dir != 0) { 
			printfDx("������:%d\n",collision_dir);
			break; 
		}
	}


	count++;
	if (PAD_INPUT::GetLStick().x >= 10000 && collision_dir != 2)
	{
		location.x += speed_x;
		if (speed_x < 5.0)
		{
			speed_x = speed_x + 0.25;
		}
	}
	else if (PAD_INPUT::GetLStick().x <= -1000 && collision_dir != 4)
	{
		location.x += speed_x;
		if (speed_x > -5.0)
		{
			speed_x = speed_x - 0.25;
		}
	}
	else
	{
		if (speed_x > 0)
		{
			speed_x--;
		}
	}

	collision_dir = 0;

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		Shoot_Gun();
	}


	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B) && fuel > 0)
	{
		not_jet_count = 0;
		jump_power = jump - GRAVITY;

		jump += 0.25;
		fuel -= 0.25;


		if (jump_power > 10)
		{
			jump_power = 10.0;
		}

		if (fuel < 0)
		{
			fuel = 0;
		}

		if (location.y > 0)
		{
			location.y -= jump_power;
		}
	}
	else
	{
		jump_power = 0;
		jump = 10;
		location.y += 10;


		if (location.y > 400)
		{
			location.y = 400;
		}

		if (not_jet_count++ >= 120)
		{
			if (fuel < 100)
			{
				fuel += 2.5;
			}
			else
			{
				fuel = 100;
			}
		}

		if (not_jet_count >= 120)
		{
			not_jet_count = 120;
		}
	}



	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i]->GetDeleteFlg())
		{
			bullet[i] = nullptr;
			SortBullet(i);
		}
		else
		{
			bullet[i]->Update();
		}
	}
}

//-----------------------------------
// �e�𔭎�
//-----------------------------------
void Player::Shoot_Gun()
{
	if (count % 30 == 0)
	{
		bullet[bullet_count++] = new Bullet(location.x, location.y);
		if (bullet_count >= 30)
		{
			bullet_count = 30;
		}
	}
}

//-----------------------------------
// �e����בւ�
//-----------------------------------
void Player::SortBullet(int delete_bullet)
{
	for (int i = delete_bullet + 1; i < 30; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet_count--;
			break;
		}
		if (bullet[i - 1] == nullptr)
		{
			bullet[i - 1] = bullet[i];
			bullet[i] = nullptr;
		}
	}
}