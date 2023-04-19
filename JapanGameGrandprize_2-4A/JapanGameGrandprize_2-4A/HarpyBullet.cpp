#include "HarpyBullet.h"
#include "CameraWork.h"

//�n�[�s�B�̉������U���̈ړ����x
#define HARPY_BULLET_SPEED 8

//�n�[�s�B�̉������_���[�W
#define HARPY_BULLET_DAMAGE 5

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
HarpyBullet::HarpyBullet(const Location spawn_location, const Location player_location)
{

	type = ENEMY_TYPE::WIND;
	location = spawn_location;
	radius = 5;
	speed = HARPY_BULLET_SPEED;
	image = 0;
	damage = HARPY_BULLET_DAMAGE;
	float radian; //�p�x
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
HarpyBullet::~HarpyBullet()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void HarpyBullet::Update()
{

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//�`��̂�
//-----------------------------------
void HarpyBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}
