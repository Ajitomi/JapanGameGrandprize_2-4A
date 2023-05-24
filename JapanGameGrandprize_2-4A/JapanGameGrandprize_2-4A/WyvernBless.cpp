#include "WyvernBless.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

#define WYVERN_BULLET_SPEED 7
#define WYVERN_BULLET_DAMAGE 5

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
WyvernBless::WyvernBless(const Location spawn_location, const Location player_location)
{

	location = spawn_location;
	radius = 14;
	speed = WYVERN_BULLET_SPEED;
	type = ENEMY_TYPE::FIRE;
	damage = WYVERN_BULLET_DAMAGE;

	direction = atan2f((player_location.y + 10) - location.y, (player_location.x + 10) - location.x);
	x_speed = static_cast<int>(speed * cosf(direction));
	y_speed = static_cast<int>(speed * sinf(direction));

	LoadDivGraph("images/enemy/wyvern_bless.png", 9, 3, 3, 1200, 1200, images);
	images_index = 0;
	frame_count = 0;

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

	frame_count++;
	if (frame_count % 3 == 0)
	{
		images_index++;
		if (WYVERN_IMAGES_NUM <= images_index)
		{
			images_index = 0;
		}
	}
}

//-----------------------------------
//�`��
//-----------------------------------
void WyvernBless::Draw() const
{

	Location draw_location = location; //�`����W
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, WYVERN_BLESS_EXTEND_RATE, 
		direction - M_PI_2, images[images_index], TRUE);
	
	
}