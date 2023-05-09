#include "Kraken.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"
#include "BulletManager.h"

//�N���[�P���̉摜  (�摜�Ȃ��A�K���Ȑ��������܂��j
#define KRAKEN_X 250
#define KRAKEN_Y 250

//�N���[�P��
#define KRAKEN_HP 500 //�iHP���߁j

//�ڋߍU��������͈�
#define ATTACK_SCOPE 100
#define ATTACK_SCOPE_Y 100

//���̍U���܂ł̎���


//�ړ��X�s�[�h
#define MOVE_SPEED 3

//�ړ�����
#define MOVE_TIME 120

//�h���b�v��(�ŏ�)
#define MIN_DROP 40

//�h���b�v��(�ő�)
#define MAX_DROP 60

//�U����
#define ATTACK_DAMAGE 20 

//�̗�
#define KRAKEN_HP 600



//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Kraken::Kraken(Location spawn_location)
{

	/*������*/
	can_delete = false;
	left_move = true;

	hp = KRAKEN_HP;
	damage = 0;


	kind = ENEMY_KIND::KRAKEN;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::WATER;
	state = ENEMY_STATE::IDOL;
	attack_state = KRAKEN_ATTACK::NONE;
	move_state = KRAKEN_STATE::NONE;

	attack_num = 1;
	drop_volume = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	location = spawn_location;

	standby_attack = 0;

	/*�����蔻��̐ݒ�*/
	area.width = KRAKEN_X;
	area.height = KRAKEN_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [WATER_DROP];
	drop_type_volume = WATER_DROP;

	int volume = 0;

	for (int i = 0; i < WATER_DROP; i++)
	{
		volume = MIN_DROP + GetRand(MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	InitDamageLog();
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Kraken::~Kraken()
{

	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	delete[] images;

}

//-----------------------------------
// �X�V
//-----------------------------------
void Kraken::Update(const Player* player, const Stage* stage)
{

	HitMapChip hit_stage = { false,nullptr }; //�X�e�[�W�Ƃ̓����蔻��
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
			}
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

	Poison();

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}

	UpdateDamageLog();
}


//-----------------------------------
//�A�C�h�����
//-----------------------------------
void  Kraken::Idol()
{
	Location scroll; //��ʃX�N���[�����l������X���W
	Location camera = CameraWork::GetCamera(); //�J����
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
void Kraken::Move(const Location player_location)
{

	int range = player_location.x - location.x;
	int range_y = player_location.y - location.y;

	//�ڋߍU��
	if (range <= ATTACK_SCOPE && range >= -ATTACK_SCOPE &&
		range_y <= ATTACK_SCOPE_Y && range_y >= -ATTACK_SCOPE_Y)
	{
		state = ENEMY_STATE::ATTACK;
		attack_state = KRAKEN_ATTACK::TENTACLE_ATTACK;
	}

		switch (attack_num)
		{
		case 0:
			attack_state = KRAKEN_ATTACK::BREATH;
			state = ENEMY_STATE::ATTACK;
			standby_attack = 40;
			break;
		case 1:
			attack_state = KRAKEN_ATTACK::HARD_ATTACK;
			state = ENEMY_STATE::ATTACK;
			standby_attack = 200;
			break;
		default:
			break;
		}

}

//-----------------------------------
//����
//-----------------------------------
void Kraken::Fall()
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
void  Kraken::Attack(const Location player_location)
{
	--standby_attack;
	if (standby_attack < 0)
	{
		switch (attack_state)
		{
		case KRAKEN_ATTACK::TENTACLE_ATTACK: //�G��U��
			state = ENEMY_STATE::MOVE;
			break;
		case KRAKEN_ATTACK::BREATH: //�u���X�U��
			AttackBreath(player_location);
			break;
		case KRAKEN_ATTACK::HARD_ATTACK: //���̉�𗎂Ƃ�
			AttackWater(player_location);
			attack_num = GetRand(1);
			state = ENEMY_STATE::MOVE;
			move_state = KRAKEN_STATE::NORMAL;
			break;
		case KRAKEN_ATTACK::NONE: //�m�[�}��
		default:
			break;
		}
	}
}

//-----------------------------------
//�U��(���̉�𗎂Ƃ��j
//-----------------------------------
void Kraken::AttackWater(Location player_location)
{
	BulletManager::GetInstance()->CreateEnemyBullet
	(new KrakenBullet(location, player_location));

}


//-----------------------------------
//�������U���i�u���X�U���j
//-----------------------------------
void Kraken::AttackBreath(const Location player_location)
{
	
		BulletManager::GetInstance()->CreateEnemyBullet
		(new KrakenBreath(location, player_location));
		
		attack_num = GetRand(1);
		state = ENEMY_STATE::MOVE;
		move_state = KRAKEN_STATE::NORMAL;
	
}


//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Kraken::Hit()
{

	//�G��o�������Ă݂�H

	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (attack_state == KRAKEN_ATTACK::TENTACLE_ATTACK)
	{
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Kraken::Death()
{

	can_delete = true;
}

//-----------------------------------
// �v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Kraken::HitBullet(const BulletBase* bullet)
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
		damage = bullet->GetDamage() * RESISTANCE_DAMAGE; //�����ɂ���;
		damage_log[i].congeniality = CONGENIALITY::RESISTANCE;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage() * WEAKNESS_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::WEAKNESS;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::POISON:
		if (!poison)
		{
			poison = true;
			poison_damage = bullet->GetDamage() * 0;
			poison_time = bullet->GetDebuffTime() * 0;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = bullet->GetDamage() * RESISTANCE_DAMAGE;
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

void Kraken::DrawHPBar(const int max_hp) const
{
	int color = GetColor(7, 255, 0);

	if (hp <= (max_hp / 2))
	{
		color = GetColor(255, 255 * static_cast<float>(hp) / max_hp, 0);
	}
	else
	{
		color = GetColor(7 + 2 * (248 * (1 - static_cast<float>(hp) / max_hp)), 255, 0);
	}

	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x000000, TRUE);
	DrawBox(160, 10, 160 + (960 * (static_cast<float>(hp) / max_hp)), 40, color, TRUE);
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x8f917f, FALSE);
}


//-----------------------------------
// �`��
//-----------------------------------
void Kraken::Draw() const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(KRAKEN_HP);
	}

	DrawDamageLog();

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);

}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Kraken::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void Kraken::Update(const ENEMY_STATE state)
{

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:
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
void Kraken::DebugDraw()
{

}
#endif //_DEBUG
