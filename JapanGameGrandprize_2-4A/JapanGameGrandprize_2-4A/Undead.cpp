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

//�h���b�v��(�ŏ�)
#define UNDEAD_MIN_DROP 0
//�h���b�v��(�ő�)
#define UNDEAD_MAX_DROP 5


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
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;
	collider = new LineCollider();

	/*�����蔻��̐ݒ�*/
	location.x = 1270.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//�h���b�v�A�C�e���̐ݒ�
	drop_item = DropItem(*type, UNDEAD_MIN_DROP, UNDEAD_MAX_DROP);

	//�r�̓����蔻��̐ݒ�
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
	delete type;
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
		if ((-area.width < location.x) && (location.x < SCREEN_WIDTH))
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

		if ((location.x < -area.width) || (SCREEN_WIDTH < location.x))
		{
			state == UNDEAD_STATE::IDOL;
		}
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

//-----------------------------------
// �v���C���[�Ƃ̋���
//-----------------------------------
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
// �v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Undead::HitBullet(Bullet* bullet)
{
	
}

//-----------------------------------
// �`��
//-----------------------------------
void Undead::Draw() const
{
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	DrawLine(arm[0].x, arm[0].y, arm[1].x, arm[1].y, 0xffffff, 5);
}

LineCollider Undead::GetLineCollider() const
{
	return *collider;
}
