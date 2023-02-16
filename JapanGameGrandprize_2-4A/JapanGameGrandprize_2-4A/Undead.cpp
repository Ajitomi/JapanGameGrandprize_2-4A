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
#define UNDEAD_MIN_DROP 0u
//�h���b�v��(�ő�)
#define UNDEAD_MAX_DROP 5u

//�h���b�v�����ސ�
#define UNDEAD_DROP 4

//�̗�
#define UNDEAD_HP 100

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead(Player* player)
{
	/*������*/
	hp = 0;
	damage = 0;
	attack_interval = 0;
	attack = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;
	drop_volume = 0;

	/*�����蔻��̐ݒ�*/
	location.x = 640.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [UNDEAD_DROP];

	int volume = 0;
	for (int i = 0; i < UNDEAD_DROP; i++)
	{
		volume = UNDEAD_MIN_DROP + GetRand(UNDEAD_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	//�h���b�v�A�C�e���̏�����
	drop_item = new Item * [drop_volume];
	for (int i = 0; i < static_cast<int>(drop_volume); i++)
	{
		drop_item[i] = nullptr;
	}

	this->player = player;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Undead::~Undead()
{
	for (int i = 0; i < UNDEAD_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;

	for (int i = 0; i < drop_volume; i++)
	{
		delete drop_item[i];
	}
	delete[] drop_item;

	delete type;
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
		DistancePlayer();

		location.x += speed;

		if ((location.x < -area.width) || (SCREEN_WIDTH < location.x))
		{
			state = UNDEAD_STATE::IDOL;
		}
		break;
	case UNDEAD_STATE::ATTACK:
		break;
	case UNDEAD_STATE::DEATH:
		for (int i = 0; i < drop_volume; i++)
		{
			if (drop_item[i] == nullptr)
			{
				break;
			}

			drop_item[i]->Update(player);
		}
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}

	if (CheckHp() && (state != UNDEAD_STATE::DEATH))
	{
		state = UNDEAD_STATE::DEATH;
		CreateDropItem(UNDEAD_DROP,location);
	}
}


//-----------------------------------
// �v���C���[�Ƃ̋���
//-----------------------------------
void Undead::DistancePlayer()
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
	if (state != UNDEAD_STATE::DEATH)
	{
		DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	}
	else
	{
		for (int i = 0; i < drop_volume; i++)
		{
			if (drop_item[i] == nullptr)
			{
				break;
			}
			drop_item[i]->Draw();
		}
	}
}

//-----------------------------------
//��Ԃ̎擾
//-----------------------------------
UNDEAD_STATE Undead::GetState() const
{
	return state;
}
