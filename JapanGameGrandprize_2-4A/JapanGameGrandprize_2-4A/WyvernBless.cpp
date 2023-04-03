#include "WyvernBless.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

#define MAGE_BULLET_SPEED 5
#define MAGE_BULLET_DAMAGE 2

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
WyvernBless::WyvernBless(const ENEMY_TYPE type,
	const Location spawn_location, const Location player_location)
{

	location = spawn_location;
	radius = 14;
	speed = MAGE_BULLET_SPEED;
	this->type = type;

	image = 0;
	damage = MAGE_BULLET_DAMAGE;
	float radian; //�p�x
	radian = atan2f((player_location.y - 10) - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
WyvernBless::~WyvernBless()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void WyvernBless::Update()
{

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//�`��
//-----------------------------------
void WyvernBless::Draw() const
{

	Location draw_location = location; //�`����W
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, radius, 0xff0000, TRUE);
	
}