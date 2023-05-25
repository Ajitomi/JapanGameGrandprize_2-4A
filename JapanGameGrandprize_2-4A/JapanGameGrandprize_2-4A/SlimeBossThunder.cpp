#include "SlimeBossThunder.h"
#include "CameraWork.h"

//�X���C���{�X�̉������U���̈ړ����x
#define BULLET_SPEED 20

//�X���C���{�X�̉������_���[�W
#define BULLET_DAMAGE 20
#define BULLET_RADIUS 25

#define ORIENTATION_TIME 10
#define IMAGE_TYPE_CHANGE_TIME 5


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
	cloud_location.y = 280;
	image_type = 0;
	image_type_change_time = 0;

	for (int i = 0; i < LOCATION_DATA; i++)
	{
		old_location[i] = location;
		old_radius[i] = BULLET_RADIUS;
	}

	radius = BULLET_RADIUS;
	speed = BULLET_SPEED;
	damage = BULLET_DAMAGE;
	
	left_move = TRUE;

	y_speed = speed;
	if (left_move)x_speed = -(speed / 2);
	else x_speed = (speed / 2);

	orientation_time = ORIENTATION_TIME;
	data_switch = 0;
	
	magic_circle_image = LoadGraph("Images/Enemy/magic_circle_2.png");
	LoadDivGraph("Images/Enemy/slime_boss_thunder.png", 8, 8, 1, 480, 480, image);


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
	location.y += y_speed;

	if (++image_type_change_time >= IMAGE_TYPE_CHANGE_TIME)
	{
		if (image_type < 7)image_type++;
		image_type_change_time = 0;
	}
}

//-----------------------------------
//�`��̂�
//-----------------------------------
void SlimeBossThunder::Draw() const
{
	/*float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0x000000, true);*/

	Draw_Cloud();

	Location draw_location = cloud_location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;
	
	DrawRotaGraph(draw_location.x, draw_location.y + 240, 1, 0, image[image_type], true, false);

	
}

void SlimeBossThunder::Draw_Cloud()const
{
	Location draw_location = cloud_location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawRotaGraph(draw_location.x, draw_location.y, 1, 0 , magic_circle_image, true, false);
}
