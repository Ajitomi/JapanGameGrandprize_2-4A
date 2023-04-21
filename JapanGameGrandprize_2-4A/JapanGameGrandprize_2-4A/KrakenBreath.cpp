#include "KrakenBreath.h"
#include"CameraWork.h"

//�u���X�U���́i�e�́j���x
#define KRAKEN_SPEED 10;

//�u���X�U���̍U����
#define BULLET_DAMAGE 45


KrakenBreath::KrakenBreath(Location spawn_location, Location player_location)
{
	type = ENEMY_TYPE::WATER;
	location = spawn_location;
	radius = 5;
	speed = KRAKEN_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;
	float radian; //�p�x
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

KrakenBreath::~KrakenBreath()
{

}

void KrakenBreath::Update()
{
	location.x += x_speed;
	location.y += y_speed;
}

void KrakenBreath::Draw() const
{
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}
