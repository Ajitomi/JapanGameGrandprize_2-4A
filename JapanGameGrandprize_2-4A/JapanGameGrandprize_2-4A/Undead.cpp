#include "Undead.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Define.h"
#include "CameraWork.h"
#include "EnemySE.h"


//�U��������͈�
#define UNDEAD_ATTACK_DISTANCE 50

//���̍U���܂ł̎���
#define UNDEAD_ATTACK_INTERVAL 30

//�ǂ�������͈�
#define UNDEAD_TRACKING_DISTANCE 170

//�����X�s�[�h
#define UNDEAD_SPEED 2

//�h���b�v��
#define UNDEAD_MIN_DROP 1
#define UNDEAD_DROP 7

//�U����
#define UNDEAD_ATTACK_DAMAGE 10

//�̗�
#define UNDEAD_HP 100

//�ړ��摜
#define UNDEAD_MOVE_IMAGES 5

//�U���摜
#define UNDEAD_ATTACK_IMAGES 4

//�摜
#define UNDEAD_IMAGES UNDEAD_MOVE_IMAGES + UNDEAD_ATTACK_IMAGES

#define UNDEAD_ANIMATION 10

#define UNDEAD_WIDTH 40
#define UNDEAD_HEIGHT 90


//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead(Location spawn_location)
{

	/*������*/
	can_delete = false;
	left_move = true;
	attack = false;

	hp = 100;
	damage = 0;
	attack_interval = 0;
	animation = 0;
	old_distance = 0;

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
	location = spawn_location;
	/*�����蔻��̐ݒ�*/
	area.width = UNDEAD_WIDTH;
	area.height = UNDEAD_HEIGHT;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= area.height / 2;
	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < SOIL_DROP; i++)
	{
		volume = UNDEAD_MIN_DROP + GetRand(UNDEAD_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	images = new int[UNDEAD_IMAGES];
	LoadDivGraph("Images/Enemy/undead.png", UNDEAD_IMAGES, UNDEAD_IMAGES, 1, 250, 250, images);
	GetGraphSizeF(images[0], &size.width, &size.height);
	InitDamageLog();
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

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
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

			location.y = chip_location.y -
				(chip_area.height / 2) - (area.height / 2);

			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			if (hit_direction == STAGE_DIRECTION::TOP)
			{
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

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
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
	UpdateDamageLog();
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
		PlaySoundMem(EnemySE::GetEnemySE(kind).attack, DX_PLAYTYPE_BACK);

		state = ENEMY_STATE::ATTACK;
		area.width += UNDEAD_WIDTH / 2;
		image_argument = UNDEAD_MOVE_IMAGES;
		animation = 0;
	
		if (player_location.x <= location.x)
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
	else if(distance < UNDEAD_TRACKING_DISTANCE && (UNDEAD_TRACKING_DISTANCE < old_distance)) //���͈͓����ƃv���C���[��ǂ�������
	{
		if (player_location.x <= location.x)
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
	old_distance = distance;
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Undead::Idol()
{

	if (!ScreenOut())
	{
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

//-----------------------------------
//�ړ�
//-----------------------------------
void Undead::Move(const Location player_location)
{	

	DistancePlayer(player_location);

	location.x += speed;

	MoveAnimation();
}

//-----------------------------------
//����
//-----------------------------------
void Undead::Fall()
{

	location.y += speed;
	if (speed < GRAVITY)
	{
		speed += ENEMY_FALL_SPEED;
	} 
}

//-----------------------------------
//�U��
//-----------------------------------
void  Undead::Attack(const Location player_location)
{
	AttackAnimation();

	if (UNDEAD_IMAGES - 1 <= image_argument)
	{
		attack = false;
		state = ENEMY_STATE::MOVE;
		attack_interval = UNDEAD_ATTACK_INTERVAL;
		area.width = UNDEAD_WIDTH;
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

	int i;
	int damage = 0;

	for (i = 0; i < LOG_NUM; i++)
	{
		if (!damage_log[i].log)
		{
			break;
		}
	}

	if (LOG_NUM <= i)
	{
		for (i = 0; i < LOG_NUM - 1; i++)
		{
			damage_log[i] = damage_log[i + 1];
		}
		i = LOG_NUM - 1;

	}

	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::POISON:
		damage = bullet->GetDamage();
		if (!poison)
		{
			poison = true;
			poison_damage = bullet->GetDamageParSecond();
			poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		if (!paralysis)
		{
			paralysis_time = bullet->GetDebuffTime() * 0;
		}
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}

	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
	hp -= damage;

	if (hp < 0)
	{
		hp = 0;
	}
}

//-----------------------------------
//�ړ����̃A�j���[�V����
//-----------------------------------
void Undead::MoveAnimation()
{

	animation++;

	if (animation % UNDEAD_ANIMATION == 0)
	{
		image_argument = ++image_argument % UNDEAD_MOVE_IMAGES;
	}
}

//-----------------------------------
//�U�����̃A�j���[�V����
//-----------------------------------
void Undead::AttackAnimation()
{

	animation++;

	if (animation % (UNDEAD_ANIMATION / 2) == 0)
	{
		image_argument = ++image_argument;
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

	Area center;

	if (left_move)
	{
		center.width = (size.width / 4) * 3;
	}
	else
	{
		center.width = (size.width / 4);
	}
	center.height = size.height / 2;


	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(UNDEAD_HP);
	}
	
	DrawDamageLog();

	DrawRotaGraph2F(draw_location.x, draw_location.y, center.width, center.height,
		0.4, 0,images[image_argument], TRUE, !left_move);

}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Undead::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void Undead::Update(const ENEMY_STATE state)
{

	if (this->state != state)
	{
		if (state != ENEMY_STATE::ATTACK)
		{
			area.width = UNDEAD_WIDTH;
		}
		else
		{
			area.width += UNDEAD_WIDTH / 3;
		}
	}
	this->state = state;
	switch (this->state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		MoveAnimation();
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:
		AttackAnimation();
		if (UNDEAD_IMAGES - 1 <= image_argument)
		{
			image_argument = UNDEAD_MOVE_IMAGES;
		}
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}
}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void Undead::DebugDraw()
{

	Area center;
	center.width = (size.width / 4) * 3;
	center.height = size.height / 2;

	DrawRotaGraph2F(location.x, location.y, center.width, center.height,
		0.4, 0,images[image_argument], TRUE, !left_move);

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xff0000, FALSE);
}
#endif //_DEBUG