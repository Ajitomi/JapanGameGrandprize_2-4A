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

	type = ENEMY_TYPE::WATER;
	location = spawn_location;
	location.y += 18;
	radius = BULLET_RADIUS;
	//speed = BULLET_SPEED;
	damage = BULLET_DAMAGE;
	float radian; //�p�x
	gravity_power = 0;

	x_speed = -((location.x - player_location.x) / 60);
	y_speed = BULLET_SPEED;

	color = GetColor(24, 168, 203);
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

	DrawCircle(x, y, radius, color, TRUE);
}

