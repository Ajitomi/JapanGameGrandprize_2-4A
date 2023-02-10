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
#define UNDEAD_SPEED -2

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead()
{
	/*������*/
	damage = 0;
	attack_interval = 0;
	attack = 0;
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
	for (int i = 0; i < 2; i++)
	{
		arm[i].x = 1270.0f - (50 * i);
		arm[i].y = 460.0f;
		collider->SetLocation(arm[i], i);

	}	
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Undead::~Undead()
{
	delete collider;
}

//-----------------------------------
// �X�V
//-----------------------------------
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
		for (int i = 0; i < 2; i++)
		{
			arm[i].x += speed;
			collider->SetLocation(arm[i], i);
		}
		location.x += speed;

		break;
	case UNDEAD_STATE::ATTACK:
		Attack();
		break;
	case UNDEAD_STATE::DEATH:
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}
}

//-----------------------------------
// �U��
//-----------------------------------
void Undead::Attack()
{
	
	arm[1].x += 5 * cosf(attack * (180 / 30));
	arm[1].y += 5 * sinf(attack * (180 / 30));

	collider->SetLocation(arm[1], 1);
	if (++attack % 30 == 0)
	{
		state = UNDEAD_STATE::IDOL;
		attack_interval = ATTACK_INTERVAL;
	}

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

//-----------------------------------
// �`��
//-----------------------------------
void Undead::Draw() const
{
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	DrawLine(arm[0].x, arm[0].y, arm[1].x, arm[1].y, 0xffffff, 5);
	DrawFormatString(100, 100, 0x000000, "%d", static_cast<int>(state));
}

LineCollider Undead::GetLineCollider() const
{
	return *collider;
}
