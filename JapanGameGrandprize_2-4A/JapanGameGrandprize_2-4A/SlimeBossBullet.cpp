#include "SlimeBossBullet.h"
#include "CameraWork.h"

//�h���S���̉������U���̈ړ����x
#define BULLET_SPEED 10

//�h���S���̉������_���[�W
#define BULLET_DAMAGE 30

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
	speed = BULLET_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;
	float radian; //�p�x
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
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

