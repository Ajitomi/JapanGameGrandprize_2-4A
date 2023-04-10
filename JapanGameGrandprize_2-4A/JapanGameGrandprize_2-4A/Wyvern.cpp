#include "Wyvern.h"
#include "Player.h"
#include "BulletManager.h"
#include "WyvernBless.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

//�ړ��X�s�[�h
#define WYVERN_MOVE_SPEED 2

//���P�U���X�s�[�h
#define WYVERN_ASSAULT_SPEED 10

//���P�U���ňړ��ł����
#define WYVERN_ASSAULT_DISTANCE 700
//���P�U���̏I������
#define ASSAULT_END_DISTANCE 50

//���P�U���̃_���[�W
#define WYVERN_ASSAULT_DAMAGE 15

#define WYVERN_MIN_DROP 1
#define WYVERN_DROP 8

//�̗�
#define WYVERN_HP 150

//�u���X�̃��[�g
#define WYVERN_SHOT_RATE 40

//�u���X�̃C���^�[�o��
#define BLESS_INTERVAL 300

//�O�A�u���X�̃C���^�[�o��
#define TRIPLE_BLESS_INTERVAL 600

//���P�U��
#define ASSAULT_INTERVAL 480

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Wyvern::Wyvern(Location spawn_location)
{
	/*������*/
	can_delete = false;
	left_move = true;
	attack_end = false;
	attack = false;

	hp = WYVERN_HP;
	damage = 0;

	bless_interval = BLESS_INTERVAL;
	triple_bless_interval = TRIPLE_BLESS_INTERVAL;
	assault_interval = ASSAULT_INTERVAL;

	shot_rate = 0;
	shot_count = 0;
	assault_speed.x = 0;
	assault_speed.y = 0;

	image_argument = 0;
	speed = 0;
	kind = ENEMY_KIND::WYVERN;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::FIRE;
	state = ENEMY_STATE::IDOL;
	attack_state = WYVERN_ATTACK::NONE;
	now_assault = false;
	drop_volume = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	location = spawn_location;
	assault_start = location;

	/*�����蔻��̐ݒ�*/
	area.width = 40;
	area.height = 80;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [FIRE_DROP];
	drop_type_volume = FIRE_DROP;

	int volume = 0;

	for (int i = 0; i < FIRE_DROP; i++)
	{
		volume = WYVERN_MIN_DROP + GetRand(WYVERN_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	hit_stage.hit = false;
	hit_stage.chip = nullptr;
	images = nullptr;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Wyvern::~Wyvern()
{
	delete[] images;
}

//-----------------------------------
//�X�V
//-----------------------------------
void Wyvern::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//�O�̍��W

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		if (bless_interval < 0) //�u���X�Ɉڍs
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::BLESS;
			break;
		}

		if (triple_bless_interval < 0) //�g���v���u���X�Ɉڍs
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::TRIPLE_BRACE;
			break;
		}

		if (assault_interval < 0) //�A�T���g�Ɉڍs
		{
			float radian; //�p�x

			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::ASSAULT;
			now_assault = true;
			radian = atan2f((player->GetLocation().y - 10) - location.y,
				(player->GetLocation().x - 10) - location.x);
			assault_speed.x = WYVERN_ASSAULT_SPEED * cosf(radian);
			assault_speed.y = WYVERN_ASSAULT_SPEED * sinf(radian);
			assault_start = location;
			break;
		}
		break;
	case ENEMY_STATE::FALL:
		Fall();
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());

		if (attack_state == WYVERN_ATTACK::ASSAULT)
		{
			hit_stage = HitStage(stage);

			if (hit_stage.hit)
			{
				location = old_location;

				assault_speed.x = -assault_speed.x;
				assault_speed.y = -assault_speed.y;
			}
		}
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}
	Poison();
	Paralysis();

	if ((state != ENEMY_STATE::DEATH) && (state != ENEMY_STATE::IDOL))
	{
		bless_interval--;
		triple_bless_interval--;
		assault_interval--;
	}

	if (CheckHp() && (state != ENEMY_STATE::DEATH))
	{
		state = ENEMY_STATE::DEATH;
	}
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Wyvern::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -WYVERN_MOVE_SPEED;
		}
		else
		{
			speed = WYVERN_MOVE_SPEED;
		}
	}
}

//-----------------------------------
//�ړ�
//-----------------------------------
void Wyvern::Move(const Location player_location)
{
	if (ScreenOut())
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//�ړ����̃A�j���[�V����
//-----------------------------------
void Wyvern::MoveAnimation()
{

}

//-----------------------------------
//����
//-----------------------------------
void Wyvern::Fall()
{

}

//-----------------------------------
//�U��
//-----------------------------------
void Wyvern::Attack(const Location player_location)
{
	switch (attack_state)
	{
	case WYVERN_ATTACK::BLESS:
		Bless(player_location);
		attack_end = true;
		break;
	case WYVERN_ATTACK::TRIPLE_BRACE:
		TripleBless(player_location);
		break;
	case WYVERN_ATTACK::ASSAULT:
		Assault(player_location);
		break;
	case WYVERN_ATTACK::NONE:
		break;
	default:
		break;
	}

	if(attack_end)
	{
		state = ENEMY_STATE::MOVE;
		switch (attack_state) //�C���^�[�o���̐ݒ�
		{
		case WYVERN_ATTACK::BLESS:
			bless_interval = BLESS_INTERVAL;
			break;
		case WYVERN_ATTACK::TRIPLE_BRACE:
			triple_bless_interval = TRIPLE_BLESS_INTERVAL;
			shot_count = 0;
			break;
		case WYVERN_ATTACK::ASSAULT:
			assault_interval = ASSAULT_INTERVAL;
			assault_speed.x = 0;
			assault_speed.y = 0;
			break;
		case WYVERN_ATTACK::NONE:
			break;
		default:
			break;
		}
		attack_state = WYVERN_ATTACK::NONE;
		attack_end = false;
		attack = false;
	}
}

//-----------------------------------
//�u���X
//-----------------------------------
void Wyvern::Bless(const Location player_location)
{
	BulletManager::GetInstance()->
		CreateEnemyBullet(new WyvernBless(location, player_location));
}

//-----------------------------------
//�g���v���u���X
//-----------------------------------
void Wyvern::TripleBless(const Location player_location)
{
	shot_rate++;

	if (shot_rate % WYVERN_SHOT_RATE == 0)
	{
		BulletManager::GetInstance()->
			CreateEnemyBullet(new WyvernBless(location, player_location));
		shot_count++;
	}

	if (3 <= shot_count)
	{
		attack_end = true;
	}

	
}

//-----------------------------------
//���P�U��
//-----------------------------------
void Wyvern::Assault(const Location)
{
	float distance = 0; //���P�U�����n�߂��ʒu����̋���
	Location distance_location; //x��y���ꂼ��̋��P�U�����n�߂��ʒu����̋���

	location = location + assault_speed;
	distance_location = assault_start - location;

	//���P�U�����n�߂��ʒu����̋����̌v�Z
	distance = sqrtf(powf(distance_location.x, 2) + powf(distance_location.y, 2));

	if (WYVERN_ASSAULT_DISTANCE < distance)
	{
		assault_speed.x = -assault_speed.x;
		assault_speed.y = -assault_speed.y;
		now_assault = false;
	}

	if (!now_assault)
	{
		if (distance < ASSAULT_END_DISTANCE)
		{
			attack_end = true;
		}
	}
}

//-----------------------------------
// �U�����Ă��Ȃ�
//-----------------------------------
void Wyvern::AttackNone()
{

}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Wyvern::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (!attack)
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::NORMAL };
		ret.damage = WYVERN_ASSAULT_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
		now_assault = false;
		assault_speed.x = -assault_speed.x;
		assault_speed.y = -assault_speed.y;
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Wyvern::Death()
{

}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Wyvern::HitBullet(const BulletBase* bullet)
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
		damage = bullet->GetDamage() * RESISTANCE_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::RESISTANCE;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage() * WEAKNESS_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::WEAKNESS;
		break;
	case ATTRIBUTE::POISON:
		if (!poison)
		{
			poison = true;
			poison_damage = bullet->GetDamage();
			poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::RESISTANCE;
		if (!paralysis)
		{
			paralysis_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
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
}

//-----------------------------------
//�`��
//-----------------------------------
void Wyvern::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(WYVERN_HP);
	}
	DrawDamageLog();

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xff0000, TRUE);
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Wyvern::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//�X�V(DotByDot)
//-----------------------------------
void Wyvern::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void Wyvern::DebugDraw()
{

}
#endif //_DEBUG