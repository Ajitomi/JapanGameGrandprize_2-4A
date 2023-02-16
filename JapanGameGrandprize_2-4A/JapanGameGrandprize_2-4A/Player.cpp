#include "Player.h"
#include "DxLib.h"
#include "NormalBullet.h"
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
	gravity_down = 0.0;
	for (int i = 0; i < 30; i++)
	{
		bullet = new Bullet * [30];
		bullet[i] = nullptr;
	}

	i = 0;

	attribute[0] = Attribute::normal;
	attribute[1] = Attribute::explosion;
	attribute[2] = Attribute::melt;
	attribute[3] = Attribute::poison;
	attribute[4] = Attribute::paralysis;
	attribute[5] = Attribute::heal;

	for (int i = 0; i < 6; i++)
	{
		attribute_c[i] = i;
	}

	player_state = PlayerState::stop;

	display_attribute = 0;

	hp = 0;

	beam = nullptr;

	stage = nullptr;

	player = this;


	//GetGraphSize(image, &image_size_x, &image_size_y);
}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Player::Player(Stage* stage)
{
	this->stage = stage;
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
	gravity_down = 0.0;
	bullet = new Bullet * [30];
	for (int i = 0; i < 30; i++)
	{
		bullet[i] = nullptr;
	}

	i = 0;

	attribute[0] = Attribute::normal;
	attribute[1] = Attribute::explosion;
	attribute[2] = Attribute::melt;
	attribute[3] = Attribute::poison;
	attribute[4] = Attribute::paralysis;
	attribute[5] = Attribute::heal;

	for (int i = 0; i < 6; i++)
	{
		attribute_c[i] = i;
	}

	player_state = PlayerState::stop;

	display_attribute = 0;

	hp = 100;

	beam = nullptr;

	stage = new Stage();

	player = this;


	//GetGraphSize(image, &image_size_x, &image_size_y);
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Player::~Player()
{
	for (int i = 0; i < 30; i++)
	{
		delete bullet[i];
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

	DrawBox(x, y, x + image_size_x, y + image_size_y, 0x00ff00, TRUE);

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}

	//if (beam != nullptr)
	//{
	//	beam->Draw();
	//}
	DrawFormatString(0, 0, 0x00ff00, "%f %f", jump_power, fuel);



	SetFontSize(30);

	//��̑I����
	if (display_attribute - 1 < 0)
	{
		DrawFormatString(1000, 10, 0x778877, "%d", attribute_c[display_attribute + 5]);
	}
	else
	{
		DrawFormatString(1000, 10, 0x778877, "%d", attribute_c[display_attribute - 1]);
	}
	//���̑I����
	if (display_attribute + 1 > 5)
	{
		DrawFormatString(1000, 90, 0x778877, "%d", attribute_c[display_attribute - 5]);
	}
	else
	{
		DrawFormatString(1000, 90, 0x778877, "%d", attribute_c[display_attribute + 1]);
	}
	//���݂̑I����
	DrawFormatString(1000, 50, 0x778877, "%d", attribute_c[display_attribute]);

	DrawFormatString(0, 400, 0x999999, "%d", hp);
}

//-----------------------------------
// �X�V
//-----------------------------------
void Player::Update()
{
	count++;


	//�X�e�B�b�N�E����
	if (PAD_INPUT::GetLStick().x >= 10000)
	{
		RightMove();
	}
	//�X�e�B�b�N������
	else if (PAD_INPUT::GetLStick().x <= -10000)
	{
		LeftMove();
	}
	//�X�e�B�b�N������
	else
	{
		NotInputStick();
	}

	//RB�{�^������
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		if (count % 30 == 0)
		{
			bullet_count++;
			Shoot_Gun();
		}
	}

	//B�{�^������
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B) && fuel > 0)
	{
		Jump();
	}
	//B�{�^��������
	else
	{
		NotJump();
	}

	//B�{�^�������
	if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B))
	{
		player_state = PlayerState::down;
	}



	//�e�̃A�b�v�f�[�g�Ăяo��
	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			if (bullet[i]->GetEfectFlg())
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

	//�e�̑����̐؂�ւ�����
	Element_Update();
	
}

//�X�e�B�b�N����͂��Ă��Ȃ��Ƃ�
void Player::NotInputStick()
{
	if (speed_x > 0)
	{
		if (player_state == PlayerState::jump || player_state == PlayerState::down)
		{
			speed_x -= JUMP_INERTIA;
		}
		else
		{
			speed_x -= WARK_INERTIA;
		}

		if (speed_x < 0)
		{
			speed_x = 0;
		}
	}

	if (speed_x < 0)
	{
		if (player_state == PlayerState::jump || player_state == PlayerState::down)
		{
			speed_x += JUMP_INERTIA;
		}
		else
		{
			speed_x += WARK_INERTIA;
		}

		if (speed_x > 0)
		{
			speed_x = 0;
		}
	}

	if (speed_x > -JUMP_INERTIA && speed_x < JUMP_INERTIA)
	{
		speed_x = 0;
	}

	location.x += speed_x;
}

//���ړ�
void Player::LeftMove()
{
	if (player_state == PlayerState::jump || player_state == PlayerState::down)
	{
		if (speed_x > -5.0)
		{
			speed_x = speed_x - JUMP_INERTIA;
		}
		else
		{
			speed_x = -5.0;
		}
	}
	else
	{
		player_state = PlayerState::move_left;
		if (speed_x > -5.0)
		{
			speed_x = speed_x - WARK_INERTIA;
		}
		else
		{
			speed_x = -5.0;
		}
	}
	location.x += speed_x;
}

//�E�ړ�
void Player::RightMove()
{
	if (player_state == PlayerState::jump || player_state == PlayerState::down)
	{
		if (speed_x < 5.0)
		{
			speed_x = speed_x + JUMP_INERTIA;
		}
		else
		{
			speed_x = 5.0;
		}
	}
	else
	{
		player_state = PlayerState::move_right;
		if (speed_x < 5.0)
		{
			speed_x = speed_x + WARK_INERTIA;
		}
		else
		{
			speed_x = 5.0;
		}
	}

	location.x += speed_x;
}

//�W�����v
void Player::Jump()
{
	player_state = PlayerState::jump;
	not_jet_count = 0;
	jump_power = jump - GRAVITY;

	gravity_down = 0.0;

	jump += 0.25;
	fuel -= 0.25;


	if (jump_power > 10)
	{
		jump_power = 10.0;
	}

	if (fuel < 0)
	{
		fuel = 0;
		player_state = PlayerState::down;
	}

	if (location.y > 0)
	{
		location.y -= jump_power;
	}
}

//�W�����v���ĂȂ�
void Player::NotJump()
{
	if (jump_power > 0)
	{
		jump_power -= 0.5;
		if (location.y > 0)
		{
			location.y -= jump_power;
		}
		else
		{
			jump_power = 0;
		}
	}
	else
	{
		jump_power = 0;
		jump = 10;

		if (location.y < 400)
		{
			location.y += gravity_down;
		}
		else
		{
			player_state = PlayerState::stop;
		}
		gravity_down += 0.25;



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
}

//-----------------------------------
// �e�𔭎�
//-----------------------------------
void Player::Shoot_Gun()
{
	switch (display_attribute)
	{
	case 0:
		for (i = 0; i < bullet_count; i++)
		{
			if (bullet[i] == NULL)
			{
				bullet[i] = new NormalBullet(location.x, location.y);
			}
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	default:
		break;
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

//������ύX
void Player::Element_Update()
{
	if (PAD_INPUT::GetRStick().y > 5000)
	{
		if (select_count % 20 == 0)
		{
			display_attribute--;
			if (display_attribute < 0)
			{
				display_attribute = 5;
			}
		}
	}

	if (PAD_INPUT::GetRStick().y < -5000)
	{
		if (select_count % 20 == 0)
		{
			display_attribute++;
			if (display_attribute > 5)
			{
				display_attribute = 0;
			}
		}
	}

	select_count++;
}

//�_���[�W���󂯂���
void Player::Hp_Damage(int damage_value)
{
	hp -= damage_value;
	if (hp <= 0)
	{
		hp = 0;
		player_state = PlayerState::death;
	}
}

//��
void Player::Hp_Heal(int heal_value)
{
	hp += heal_value;
	if (hp >= HP_MAX)
	{
		hp = HP_MAX;
	}
}