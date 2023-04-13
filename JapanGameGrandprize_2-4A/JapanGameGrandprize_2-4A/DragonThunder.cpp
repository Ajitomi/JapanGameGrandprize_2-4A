#include "DragonThunder.h"
#include "CameraWork.h"

//���̈ړ����x
#define BULLET_SPEED 30

//���_���[�W
#define BULLET_DAMAGE 30

//���ҋ@���ԁi�U���\�����ԁH�j
#define ATTACK_TIME 120

DragonThunder::DragonThunder(float x, float y)
{
	type = ENEMY_TYPE::THUNDER;
	location.x = x;
	location.y = y;
	radius = 5;
	speed = BULLET_SPEED;
	thunder_time = 0;
	image = 0;
	damage = BULLET_DAMAGE;
	attack = false;
}


//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
DragonThunder::~DragonThunder()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void DragonThunder::Update()
{
	if (++thunder_time % ATTACK_TIME == 0)
	{
		attack = true;
	}

	if (attack == true)
	{
		location.y += speed;
	}

}

//-----------------------------------
//�`��̂�
//-----------------------------------
void DragonThunder::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}
