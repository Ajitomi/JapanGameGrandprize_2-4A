#include "SlimeBossBullet.h"
#include "CameraWork.h"

//�X���C���{�X�̉������U���̈ړ����x
#define BULLET_SPEED 10

//�X���C���{�X�̉������_���[�W
#define BULLET_DAMAGE 20
#define BULLET_RADIUS 12

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
SlimeBossBullet::SlimeBossBullet(Location spawn_location, Location player_location)
{
	LoadDivGraph("Images/Enemy/slimeboss_bullet.png", 12, 12, 1, 200, 200, image);

	type = ENEMY_TYPE::WATER;
	location = spawn_location;
	location.y += 18;
	radius = BULLET_RADIUS;
	image_change_time = 0;
	image_change_no = 1;
	damage = BULLET_DAMAGE;
	float radian; //�p�x
	gravity_power = 0;

	x_speed = -((location.x - player_location.x) / 60);
	y_speed = BULLET_SPEED;

	image_type = 3;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
SlimeBossBullet::~SlimeBossBullet()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void SlimeBossBullet::Update()
{
	if (++image_change_time >= 5)
	{
		image_type += image_change_no;
		if (((image_type == 9) && (image_change_no == 1)) ||
			((image_type == 5) && (image_change_no == -1)))image_change_no = -image_change_no;
		image_change_time = 0;
	}
	gravity_power++;
	y_speed = (-BULLET_SPEED + (gravity_power / 3));

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//�`��̂�
//-----------------------------------
void SlimeBossBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawRotaGraph(x, y, 0.5, 0, image[image_type], true, false);
}

