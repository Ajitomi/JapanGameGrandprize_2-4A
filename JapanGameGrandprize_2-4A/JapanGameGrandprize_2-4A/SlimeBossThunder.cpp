#include "SlimeBossThunder.h"
#include "CameraWork.h"

//�X���C���{�X�̉������U���̈ړ����x
#define BULLET_SPEED 15

//�X���C���{�X�̉������_���[�W
#define BULLET_DAMAGE 20
#define BULLET_RADIUS 25

#define ORIENTATION_TIME 10



//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
SlimeBossThunder::SlimeBossThunder(Location spawn_location)
{
	type = ENEMY_TYPE::THUNDER;
	location = spawn_location;
	//�{�X�X�e�[�W�̏k���ɂ�藎���ʒu��������
	location.y = 280;

	cloud_location = spawn_location;

	for (int i = 0; i < LOCATION_DATA; i++)
	{
		old_location[i] = location;
		old_radius[i] = BULLET_RADIUS;
	}

	radius = BULLET_RADIUS;
	speed = BULLET_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;
	
	left_move = TRUE;

	y_speed = speed;
	if (left_move)x_speed = -(speed / 2);
	else x_speed = (speed / 2);

	orientation_time = ORIENTATION_TIME;
	data_switch = 0;
	
	
	color = GetColor(255, 255, 0);
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
SlimeBossThunder::~SlimeBossThunder()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void SlimeBossThunder::Update()
{
	if (--orientation_time <= 0)
	{
		left_move = !left_move;
		x_speed = -x_speed;
		orientation_time = ORIENTATION_TIME;
	}

	location.x += x_speed;
	location.y += y_speed;

	data_switch++;
	radius = BULLET_RADIUS - (data_switch / 2);

	if (data_switch < LOCATION_DATA)
	{
		old_location[data_switch] = location;
		old_radius[data_switch] = radius;
	}

}

//-----------------------------------
//�`��̂�
//-----------------------------------
void SlimeBossThunder::Draw() const
{
	float x, y;

	for (int i = 0; i < LOCATION_DATA; i++)
	{
		x = old_location[i].x - CameraWork::GetCamera().x;
		y = old_location[i].y - CameraWork::GetCamera().y;

		DrawCircle(x, y, old_radius[i], color, TRUE);
	}

	Draw_Cloud();
}

void SlimeBossThunder::Draw_Cloud()const
{
	Location draw_location = cloud_location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	int color = GetColor(255, 255, 255);

	DrawCircle(draw_location.x, 0, 70, color, true, true);
}
