#include "GhostBullet.h"

#define GHOST_BULLET_SPEED 10
#define GHOST_BULLET_DAMAGE 10

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
GhostBullet::GhostBullet( Location spawn_location, Location player_location)
{
	type = ENEMY_TYPE::WIND;
	location = spawn_location;

	speed = GHOST_BULLET_SPEED;
	image = 0;
	damage = GHOST_BULLET_DAMAGE;
	float radian; //�p�x
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
GhostBullet::~GhostBullet()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void GhostBullet::Update()
{
	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//�`��
//-----------------------------------
void GhostBullet::Draw() const
{
	DrawCircle(location.x, location.y,3, 0xffffff, TRUE);
}