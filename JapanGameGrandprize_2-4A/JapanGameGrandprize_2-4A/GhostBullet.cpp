#include "GhostBullet.h"
#include "CameraWork.h"

#define GHOST_BULLET_SPEED 10
#define GHOST_BULLET_DAMAGE 10

//-----------------------------------
//コンストラクタ
//-----------------------------------
GhostBullet::GhostBullet( Location spawn_location, Location player_location)
{
	type = ENEMY_TYPE::WIND;
	location = spawn_location;
	radius = 5;
	speed = GHOST_BULLET_SPEED;
	image = 0;
	damage = GHOST_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
}

//-----------------------------------
// デストラクタ
//-----------------------------------
GhostBullet::~GhostBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void GhostBullet::Update()
{
	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画
//-----------------------------------
void GhostBullet::Draw() const
{
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}