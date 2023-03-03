#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Undead.h"
#include "Define.h"
#include "CameraWork.h"

//�U��������͈�
#define UNDEAD_ATTACK_DISTANCE 50

//���̍U���܂ł̎���
#define UNDEAD_ATTACK_INTERVAL 30

//�ǂ�������͈�
#define UNDEAD_TRACKING_DISTANCE 340

//�����X�s�[�h
#define UNDEAD_SPEED -2

//�h���b�v��
#define UNDEAD_MIN_DROP 0u
#define UNDEAD_MAX_DROP 5u


#define UNDEAD_ATTACK_DAMAGE 10
//�̗�
#define UNDEAD_HP 100

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead()
{
	/*������*/
	can_delete = false;
	hp = 100;
	damage = 0;
	attack_interval = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;
	attack_time = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;

	/*�����蔻��̐ݒ�*/
	location.x = 640.0f;
	location.y = 1220.0f;
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
	if (attack_interval > 0)
	{
		attack_interval--;
	}

	Poison();

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}


//-----------------------------------
// �v���C���[�Ƃ̋���
//-----------------------------------
void Undead::DistancePlayer(const Location player_location)
{
	float distance; //����Ă��鋗��

	//�v���C���[�Ƃ̋����̌v�Z
	distance = sqrtf(powf(player_location.x - location.x, 2) + powf(player_location.y - location.y, 2));

	//�U���͈͂ɓ����Ă��邩�U���܂ł̎��Ԃ�0�ȉ���������U������
	if ((distance < UNDEAD_ATTACK_DISTANCE) && (attack_interval <= 0))
	{
		state = ENEMY_STATE::ATTACK;
		attack_time = 20;
		image = 0xff0000;
	}
	else if(distance < UNDEAD_TRACKING_DISTANCE) //���͈͓����ƃv���C���[��ǂ�������
	{
		if (player_location.x < location.x)
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
//�A�C�h�����
//-----------------------------------
void Undead::Idol()
{
	Location scroll; //��ʃX�N���[�����l������X���W

	scroll.x = location.x - CameraWork::GetCamera().x;
	scroll.y = location.y - CameraWork::GetCamera().y;
	if ((-area.width < scroll.x) && (scroll.x < SCREEN_WIDTH + area.width) &&
		(-area.height < scroll.y) && (scroll.y < SCREEN_HEIGHT + area.height))
	{
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//�ړ�
//-----------------------------------
void Undead::Move(const Location player_location)
{

	Location scroll; //��ʃX�N���[�����l������X���W

	
	DistancePlayer(player_location);

	location.x += speed;

	scroll.x = location.x - CameraWork::GetCamera().x;
	scroll.y = location.y - CameraWork::GetCamera().y;

	if ((scroll.x < -area.width) || (SCREEN_WIDTH + area.width < scroll.x) || 
		(scroll.y < -area.height) || (SCREEN_HEIGHT + area.height < scroll.y))
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//�U��
//-----------------------------------
void  Undead::Attack(Location player_location)
{
	attack_time--;
	if (attack_time < 0)
	{
		state = ENEMY_STATE::MOVE;
		image = 0xffffff;
		attack_interval = UNDEAD_ATTACK_INTERVAL;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Undead::HitCheck(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (state == ENEMY_STATE::ATTACK)
	{
		if (HitBox(collider))
		{
			ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::NORMAL };
			ret.damage = UNDEAD_ATTACK_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Undead::Death()
{
	can_delete = true;
}

//-----------------------------------
// �v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
bool Undead::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //�߂�l

	if (HitSphere(bullet))
	{

		switch (bullet->GetAttribute())
		{
		case ATTRIBUTE::NORMAL:
			hp -= bullet->GetDamage();
			break;
		case ATTRIBUTE::EXPLOSION:
			hp -= bullet->GetDamage();
			break;
		case ATTRIBUTE::MELT:
			hp -= bullet->GetDamage();
			break;
		case ATTRIBUTE::POISON:
			poison_damage = bullet->GetDamage();
			poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
			break;
		case ATTRIBUTE::PARALYSIS:
			paralysis_time = bullet->GetDebuffTime() * 0;
			break;
		case ATTRIBUTE::HEAL:
			break;
		default:
			break;
		}

		ret = true;
	}

	return ret;
}

//-----------------------------------
// �`��
//-----------------------------------
void Undead::Draw() const
{
	Location draw_location; //�`��p�̍��W

	draw_location.x = location.x - CameraWork::GetCamera().x;
	draw_location.y = location.y - CameraWork::GetCamera().y;

	DrawBox(draw_location.x, draw_location.y,
		draw_location.x + area.width, draw_location.y + area.height, image, TRUE);
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Undead::GetLocation() const
{
	return location;
}