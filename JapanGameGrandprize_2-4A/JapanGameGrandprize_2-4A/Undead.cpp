#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Undead.h"
#include "Define.h"
#include "CameraWork.h"

//�U��������͈�
#define ATTACK_DISTANCE 50

//���̍U���܂ł̎���
#define ATTACK_INTERVAL 30

//�ǂ�������͈�
#define TRACKING_DISTANCE 340

//�����X�s�[�h
#define UNDEAD_SPEED -2

//�h���b�v��
#define UNDEAD_MIN_DROP 0u
#define UNDEAD_MAX_DROP 5u



//�̗�
#define UNDEAD_HP 100

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead(Player* player)
{
	/*������*/
	can_delete = false;
	hp = 0;
	damage = 0;
	attack_interval = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;
	attack_time = 0;

	/*�����蔻��̐ݒ�*/
	location.x = 640.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;
	for (int i = 0; i < SOIL_DROP; i++)
	{
		volume = UNDEAD_MIN_DROP + GetRand(UNDEAD_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	this->player = player;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Undead::~Undead()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;

	delete type;
}

//-----------------------------------
// �X�V
//-----------------------------------
void Undead::Update()
{
	float screen_x; //��ʃX�N���[�����l������X���W

	screen_x = location.x - CameraWork::GetCamera().x;

	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		if ((-area.width < screen_x) && (screen_x < SCREEN_WIDTH + area.width))
		{
			state = UNDEAD_STATE::MOVE;
		}
		break;
	case UNDEAD_STATE::MOVE:
		DistancePlayer();

		location.x += speed;

		if ((screen_x < -area.width) || (SCREEN_WIDTH + area.width < screen_x))
		{
			state = UNDEAD_STATE::IDOL;
		}
		break;
	case UNDEAD_STATE::ATTACK:
		attack_time--;
		if (attack_time < 0)
		{
			state = UNDEAD_STATE::MOVE;
			image = 0xffffff;
			attack_interval = ATTACK_INTERVAL;
		}
		break;
	case UNDEAD_STATE::DEATH:
		can_delete = true;
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}

	if (CheckHp() && state != UNDEAD_STATE::DEATH)
	{
		state = UNDEAD_STATE::DEATH;
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
		attack_time = 20;
		image = 0xff0000;
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
void Undead::HitBullet(BulletBase* bullet)
{
	
}

//-----------------------------------
// �`��
//-----------------------------------
void Undead::Draw() const
{
	Location draw_location; //�`��p�̍��W

	draw_location.x = location.x - CameraWork::GetCamera().x;
	draw_location.y = location.y - CameraWork::GetCamera().y;

	DrawBox(draw_location.x, draw_location.y, draw_location.x + area.width, draw_location.y + area.height, image, TRUE);
}

//-----------------------------------
//��Ԃ̎擾
//-----------------------------------
UNDEAD_STATE Undead::GetState() const
{
	return state;
}
