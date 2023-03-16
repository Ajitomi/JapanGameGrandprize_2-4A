#include "Undead.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Define.h"
#include "CameraWork.h"

//�U��������͈�
#define UNDEAD_ATTACK_DISTANCE 50

//���̍U���܂ł̎���
#define UNDEAD_ATTACK_INTERVAL 30

//�ǂ�������͈�
#define UNDEAD_TRACKING_DISTANCE 340

//�����X�s�[�h
#define UNDEAD_SPEED 2

//�h���b�v��
#define UNDEAD_MIN_DROP 0u
#define UNDEAD_MAX_DROP 5u

//�U����
#define UNDEAD_ATTACK_DAMAGE 10

//�̗�
#define UNDEAD_HP 100

//�ړ��摜
#define UNDEAD_MOVE_IMAGES 5

#define UNDEAD_MOVE_ANIMATION 10

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead()
{
	/*������*/
	can_delete = false;
	left_move = true;
	attack = false;

	hp = 100;
	damage = 0;
	attack_interval = 0;
	animation = 0;
	image_argument = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::SOIL;
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	attack_time = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;

	/*�����蔻��̐ݒ�*/
	location.x = 3220.0f;
	location.y = 970.0f;
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

	images = new int[UNDEAD_MOVE_IMAGES];
	LoadDivGraph("Images/Enemy/undead.png", 5, 5, 1, 40, 80, images);
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

	delete[] type;

	for (int i = 0; i < UNDEAD_MOVE_IMAGES; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;
}

//-----------------------------------
// �X�V
//-----------------------------------
void Undead::Update(const Player* player, const Stage* stage)
{
	HitMapChip hit_stage = {false,nullptr}; //�X�e�[�W�Ƃ̓����蔻��
	Location old_location = location; //�ړ��O�̍��W
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		hit_stage = HitStage(stage);
		if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
		{
			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
			{
				location = old_location;
				left_move = !left_move;
				speed = -speed;
			}
		}
		else
		{
			state = ENEMY_STATE::FALL;
			speed = 0;
		}
		break;
	case ENEMY_STATE::FALL:
		Fall();

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
		{
			Location chip_location = hit_stage.chip->GetLocation();
			Area chip_area = hit_stage.chip->GetArea();

			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			if (hit_direction == STAGE_DIRECTION::TOP)
			{
				location.y = chip_location.y - 
					(chip_area.height / 2) - (area.height / 2);

				state = ENEMY_STATE::MOVE;
				if (left_move)
				{
					speed = -UNDEAD_SPEED;
				}
				else
				{
					speed = UNDEAD_SPEED;
				}
			}
		}
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}

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
	}
	else if(distance < UNDEAD_TRACKING_DISTANCE) //���͈͓����ƃv���C���[��ǂ�������
	{
		if (player_location.x < location.x)
		{
			left_move = true;
			speed = -UNDEAD_SPEED;
		}
		else
		{
			left_move = false;
			speed = UNDEAD_SPEED;
		}
	}
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Undead::Idol()
{
	Location scroll; //��ʃX�N���[�����l���������W
	Location camera  = CameraWork::GetCamera(); //�J����
	scroll = location - camera;

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

	MoveAnimation();

	scroll.x = location.x - CameraWork::GetCamera().x;
	scroll.y = location.y - CameraWork::GetCamera().y;

	if ((scroll.x < -area.width) || (SCREEN_WIDTH + area.width < scroll.x) || 
		(scroll.y < -area.height) || (SCREEN_HEIGHT + area.height < scroll.y))
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//����
//-----------------------------------
void Undead::Fall()
{
	if (speed < GRAVITY)
	{
		speed += ENEMY_FALL_SPEED;
	} 
	location.y += speed;
}

//-----------------------------------
//�U��
//-----------------------------------
void  Undead::Attack(Location player_location)
{
	attack_time--;
	if (attack_time < 0)
	{
		attack = false;
		state = ENEMY_STATE::MOVE;
		attack_interval = UNDEAD_ATTACK_INTERVAL;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Undead::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (!attack)
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::NORMAL };
		ret.damage = UNDEAD_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
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
void Undead::HitBullet(const BulletBase* bullet)
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
}

//-----------------------------------
//�ړ����̃A�j���[�V����
//-----------------------------------
void Undead::MoveAnimation()
{
	animation++;
	if (animation % UNDEAD_MOVE_ANIMATION == 0)
	{
		image_argument = ++image_argument % UNDEAD_MOVE_IMAGES;
	}
}

//-----------------------------------
// �`��
//-----------------------------------
void Undead::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, 1.0, 0,
		images[image_argument],TRUE, !left_move);
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Undead::GetLocation() const
{
	return location;
}