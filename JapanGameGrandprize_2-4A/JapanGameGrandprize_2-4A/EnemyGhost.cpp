#include "EnemyGhost.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "BulletManager.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 80
#define GHOST_SIZE_Y 94

//�v���C���[��������
#define DETECTION_DISTANCE 400
#define DETECTION_DISTANCE_Y 300

//�����U���͈�
#define ATTACK_RANGE 160
#define ATTACK_RANGE_Y 100

#define ATTACK_MAGIC 300
#define ATTACK_MAGIC_Y 200

//���@�U���������̍d������
#define MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define PHYSICAL_STANDBY 100

//�ړ��X�s�[�h
#define SPEED 1

//�U���X�s�[�h
#define ATTACK_SPEED 2

//�h���b�v��(�ŏ�)
#define GHOST_MIN_DROP 1

//�h���b�v��(�ő�)
#define GHOST_DROP 7

//�S�[�X�g�̍U����
#define ATTACK_DAMAGE 10

#define GHOST_HP 30
//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost(Location spawn_location)
{

	can_delete = false;
	left_move = true;
	attack = false;

	vector = 0;
	attack_anime = 0;
	travel = 0;
	travel_y = 0;
	range = 0;
	range_y = 0;
	animation = 5;
	animation_time = 0;
	magic_time = 0;
	magic_num = 0;
	physical_time = 0;
	hp = GHOST_HP;
	location = spawn_location;
	standby_attack = 0;
	speed = 1.5;
	area.width = GHOST_SIZE_X;
	area.height = GHOST_SIZE_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;

	standby_time = 0;
	halt_time = 0;
	physical_attack = false;
	magic_attack = false;
	close_attack = false;
	attack_halt = false;

	kind = ENEMY_KIND::GHOST;

	images = new int[7];
	LoadDivGraph("Images/Enemy/ghostman3 .png", 6, 6, 1, 250, 250, images); //�ʏ�
	LoadDivGraph("Images/Enemy/ghostattack.png", 2, 2, 1, 250, 250, attack_image); //�U��
	GetGraphSizeF(images[0], &size.width, &size.height);
	GetGraphSizeF(attack_image[0], &attack_size.width, &attack_size.height);

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;

	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = GHOST_MIN_DROP + GetRand(GHOST_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = GHOST_STATE::NORMAL;

#ifdef _DEBUG
	ENEMY_STATE old_state = state;
#endif // _DEBUG
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
EnemyGhost::~EnemyGhost()
{

	delete[] images;
	delete[] type;

	for (int i = 0; i < WIND_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update(const class Player* player, const class Stage* stage)
{

	Location old_location = location;	//�O�̍��W
	HitMapChip hit_stage = { false,nullptr }; //�X�e�[�W�Ƃ̓����蔻��


	//�A�j���[�V�����S�[�X�g
	if (++animation_time % 10 == 0)
	{
		--animation;
		++attack_anime;
	}

	if (animation < 0)
	{
		animation = 5;
	}
	if (attack_anime > 1)
	{
		attack_anime = 0;
	}

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());
		break;
	case ENEMY_STATE::FALL:
		Fall();
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		AttackMove(player->GetLocation());
		hit_stage = HitStage(stage);

		if (attack_state == GHOST_ATTACK::PHYSICAL_ATTACK) //�ڋߍU�����̃X�e�[�W�Ƃ̓����蔻��
		{
			if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
			{
				Location chip_location = hit_stage.chip->GetLocation();
				Area chip_area = hit_stage.chip->GetArea();

				location.y = chip_location.y -
					(chip_area.height / 2) - (area.height / 2);

				STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
				hit_direction = HitDirection(hit_stage.chip);

				if (hit_direction == STAGE_DIRECTION::BOTTOM || hit_direction == STAGE_DIRECTION::TOP)
				{
					location = old_location;
					close_attack = false;
					magic_num = 0;
				}
			}
		}

		if (attack_state == GHOST_ATTACK::PHYSICAL_ATTACK) //�������U�����̃X�e�[�W�Ƃ̓����蔻��
		{
			if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
			{
				Location chip_location = hit_stage.chip->GetLocation();
				Area chip_area = hit_stage.chip->GetArea();

				location.y = chip_location.y -
					(chip_area.height / 2) - (area.height / 2);

				STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
				hit_direction = HitDirection(hit_stage.chip);

				if (hit_direction == STAGE_DIRECTION::BOTTOM || hit_direction == STAGE_DIRECTION::TOP)
				{
					attack_halt = true;
				}
			}
		}

		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}

	hit_stage = HitStage(stage);
	if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
	{
		STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
		hit_direction = HitDirection(hit_stage.chip);

		if (hit_direction == STAGE_DIRECTION::TOP || hit_direction == STAGE_DIRECTION::BOTTOM)
		{
			location = old_location;
		}
		if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
		{
			location = old_location;
			left_move = !left_move;
		}
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
	UpdateDamageLog();



}

//�A�C�h�����
void EnemyGhost::Idol()
{

	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		speed = 1.5;
	}
}

//�ړ�
void EnemyGhost::Move(const Location player_location)
{

	//�v���C���[�Ƃ̋����v�Z
	range = player_location.x - location.x;
	range_y = player_location.y - location.y;

	vector = sqrt(range * range + range_y * range_y);

	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE
		&& range_y <= DETECTION_DISTANCE_Y && range_y >= -DETECTION_DISTANCE_Y && attack_halt == false)
	{

		if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE
			&& range_y <= ATTACK_RANGE_Y && range_y >= -ATTACK_RANGE_Y
			|| close_attack == true)

		{
			state = ENEMY_STATE::ATTACK;
			attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
			standby_time = PHYSICAL_STANDBY;
			physical_attack = true;
		}
		else if(range <= ATTACK_MAGIC && range >= -ATTACK_MAGIC
			&& range_y <= ATTACK_MAGIC_Y && range_y >= -ATTACK_MAGIC_Y)
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = GHOST_ATTACK::MAGIC_ATTACK;
			standby_time = MAGIC_STANDBY;
			magic_attack = true;
			if (++magic_time % 2 == 0)
			{
				++magic_num;
				//�e�̐���
				BulletManager::GetInstance()->CreateEnemyBullet
				(new GhostBullet(location, player_location));
			}
		}

		else
		{
			if (left_move == true)
			{
				location.x -= speed;
			}
			else
			{
				location.x += speed;
			}

		}

	}
	else
	{
		if (left_move == true)
		{
			location.x -= speed;
		}
		else
		{
			location.x += speed;
		}

	}

	if (magic_num > 5)
	{
		close_attack = true;

		if (++physical_time % 10 == 0)
		{
			magic_num = 0;
			physical_time = 0;
		}
	}

	if (attack_halt == true)
	{
		if (++halt_time % 10 == 0)
		{
			halt_time = 0;
			attack_halt = false;
		}
	}

}

//-----------------------------------
//�U��
//-----------------------------------
void  EnemyGhost::Attack(const Location player_location)
{

	//�S�[�X�g�̉摜�̌��������߂�
	if (location.x < player_location.x)
	{
		left_move = false;
	}
	else if (location.x > player_location.x)
	{
		left_move = true;
	}

	standby_time--;
	if (standby_time < 0)
	{
		switch (attack_state)
		{
		case GHOST_ATTACK::PHYSICAL_ATTACK:
			attack = false;
			physical_attack = false;
			attack_state = GHOST_ATTACK::NONE;
			break;
		case GHOST_ATTACK::MAGIC_ATTACK:
			magic_attack = false;
			break;
		case GHOST_ATTACK::NONE:
			break;
		default:
			break;
		}

		standby_time = 0;
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource EnemyGhost::Hit()
{

	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (attack_state == GHOST_ATTACK::PHYSICAL_ATTACK && (!attack))
	{
			attack = true;
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
void EnemyGhost::Death()
{

	can_delete = true;
}

//-----------------------------------
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{

	//�X�N���[���ɍ��킹�ĕ`��
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;
	Area center;
	Area center1;

	if (left_move)
	{
		center.width = (size.width / 3) + 40;
		center1.width = (attack_size.width / 3) + 40;
	}
	else
	{
		center.width = (size.width / 3) - 10;
		center1.width = (attack_size.width / 3) - 40;
	}
	center.height = (size.height / 3) + 20;
	center1.height = (attack_size.width / 3) + 20;

	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(GHOST_HP);
	}
	DrawDamageLog();
	DrawWeaknessIcon();

	if (attack == false)
	{
		DrawRotaGraph2F(draw_location.x, draw_location.y, center.width, center.height,
			0.4, 0, images[animation], TRUE, !left_move);
	}
	else
	{
		DrawRotaGraph2F(draw_location.x, draw_location.y, center.width, center.height,
			0.4, 0, attack_image[attack_anime], TRUE, !left_move);
	}
}

//-----------------------------------
// �ڋߍU��
//-----------------------------------
void EnemyGhost::AttackMove(const Location player_location)
{


	if (physical_attack == true)
	{
		range = player_location.x - location.x;
		range_y = player_location.y - location.y;

		vector = sqrt(range * range + range_y * range_y);

		travel = range / vector;
		travel_y = range_y / vector;
		location.x += travel * ATTACK_SPEED;
		location.y += travel_y * ATTACK_SPEED;
	}

}

//-----------------------------------
//����
//-----------------------------------
void EnemyGhost::Fall()
{

}

//-----------------------------------
// �v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void EnemyGhost::HitBullet(const BulletBase* bullet)
{
	
	PlayHitBulletSound(bullet->GetAttribute());

	int i = 0;
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

	switch (bullet->GetAttribute()) //�󂯂��������̑���
	{
	case ATTRIBUTE::NORMAL:
		damage = 0; //����
		damage_log[i].congeniality = CONGENIALITY::INVALID;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage() * WEAKNESS_DAMAGE; //��_����
		damage_log[i].congeniality = CONGENIALITY::WEAKNESS;
		break;
	case ATTRIBUTE::MELT:
		damage = 0; //����
		damage_log[i].congeniality = CONGENIALITY::INVALID;
		break;
	case ATTRIBUTE::POISON:
		poison_damage = bullet->GetDamage() * 0; //����
		poison_time = bullet->GetDebuffTime() * 0; //����
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = 0;
		paralysis_time = bullet->GetDebuffTime() * 0; //����
		paralysis_time = bullet->GetDamage() * 0; //����
		damage_log[i].congeniality = CONGENIALITY::INVALID;
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
//���W�̎擾
//-----------------------------------
Location EnemyGhost::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void EnemyGhost::Update(const ENEMY_STATE state)
{

	if ((old_state == ENEMY_STATE::ATTACK) &&
		(state != ENEMY_STATE::ATTACK))
	{
		attack = false;
	}

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		//�A�j���[�V�����S�[�X�g
		if (++animation_time % 10 == 0)
		{
			--animation;
		}

		if (animation < 0)
		{
			animation = 5;
		}
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:

		if (!attack)
		{
			attack = true;
		}

		if (++animation_time % 10 == 0)
		{
			++attack_anime;
		}

		if (attack_anime > 1)
		{
			attack_anime = 0;
		}
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	old_state = state;
}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void EnemyGhost::DebugDraw()
{
	if (!attack)
	{
		DrawRotaGraphF(location.x, location.y, 1.3f,
			M_PI / 180, images[animation], TRUE, !left_move);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, 1.3f,
			M_PI / 180, attack_image[attack_anime], TRUE, !left_move);
	}

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xff0000, FALSE);
}
#endif //_DEBUG