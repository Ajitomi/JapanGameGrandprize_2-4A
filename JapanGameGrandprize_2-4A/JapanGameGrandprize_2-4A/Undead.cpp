#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Undead.h"
#include "Define.h"

//�U��������͈�
#define ATTACK_DISTANCE 50

//���̍U���܂ł̎���
#define ATTACK_INTERVAL 20

//�ǂ�������͈�
#define TRACKING_DISTANCE 340

//�����X�s�[�h
#define UNDEAD_SPEED 5

Undead::Undead()
{
	/*������*/
	damage = 0;
	attack_interval = 0;
	speed = UNDEAD_SPEED;
	location.x = 1270.0f;
	location.y = 430.0f;

	area.width = 40;
	area.height = 80;

	kind = ENEMY_KIND::UNDEAD;
	type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;

	collider = new LineCollider();
}

Undead::~Undead()
{
	delete collider;
}

void Undead::Update()
{
	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		if (location.x < SCREEN_WIDTH)
		{
			state = UNDEAD_STATE::MOVE;
		}
		break;
	case UNDEAD_STATE::MOVE:
		location.x -= speed;
		break;
	case UNDEAD_STATE::ATTACK:
		Attack();
		break;
	case UNDEAD_STATE::DEATH:
		break;
	default:
		break;
	}

	
}


void Undead::Attack()
{
	Location arm; //�r��̍��W
	arm = collider->GetLocation(1);


}

void Undead::DistancePlayer(Player* player)
{
	float distance; //����Ă��鋗��

	//�v���C���[�Ƃ̋����̌v�Z
	distance = sqrtf(powf(player->GetLocation().x - location.x, 2) + powf(player->GetLocation().y - location.y, 2));

	//�U���͈͂ɓ����Ă��邩�U���܂ł̎��Ԃ�0�ȉ���������U������
	if ((distance < ATTACK_DISTANCE) && (attack_interval <= 0))
	{
		state = UNDEAD_STATE::ATTACK;
	}
	else if(distance < TRACKING_DISTANCE) //���͈͓����ƃv���C���[��ǂ�������
	{
		if (player->GetLocation().x < location.x)
		{
			speed = UNDEAD_SPEED;
		}
		else
		{
			speed = -UNDEAD_SPEED;
		}
	}
	else
	{
		speed = UNDEAD_SPEED;
	}
}

void Undead::Draw() const
{
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	DrawFormatString(100, 100, 0x000000, "%d", static_cast<int>(state));
}

LineCollider Undead::GetLineCollider() const
{
	return *collider;
}
