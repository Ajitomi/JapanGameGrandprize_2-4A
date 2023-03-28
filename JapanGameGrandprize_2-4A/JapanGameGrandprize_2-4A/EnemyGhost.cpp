#include "EnemyGhost.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "BulletManager.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 60
#define GHOST_SIZE_Y 66

//�v���C���[��������
#define DETECTION_DISTANCE 500
#define DETECTION_DISTANCE_Y 300

//�����U���͈�
#define ATTACK_RANGE 100
#define ATTACK_RANGE_Y 100

//���@�U���������̍d������
#define MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define PHYSICAL_STANDBY 100

//�ړ��X�s�[�h
#define SPEED 1.5

//�U���X�s�[�h
#define ATTACK_SPEED 4.5

//�h���b�v��(�ŏ�)
#define GHOST_MIN_DROP 1

//�h���b�v��(�ő�)
#define GHOST_DROP 7

//�S�[�X�g�̍U����
#define ATTACK_DAMAGE 10

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost(Location spawn_location)
{

	can_delete = false;
	left_move = true;
	attack = false;

	vector = 0;
	travel = 0;
	travel_y = 0;
	range = 0;
	range_y = 0;
	animation = 0;
	animation_time = 0;
	magic_time = 1;
	magic_num = 0;
	physical_time = 0;
	hp = 10;
	location = spawn_location;
	//location.y = 250; //�e�X�g
	standby_attack = 0;
	speed = 1.5;
	area.width = GHOST_SIZE_X;
	area.height = GHOST_SIZE_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;

	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	kind = ENEMY_KIND::GHOST;

	images = new int[7];
	LoadDivGraph("Images/Enemy/ghostman3.png", 6, 6, 1, 60, 66, images);
	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;

	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = GHOST_MIN_DROP + GetRand(GHOST_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = GHOST_STATE::NORMAL;
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
	if (animation_time++ % 10 == 0)
	{
		animation++;
	}

	if (animation > 5)
	{
		animation = 0;
	}

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
		}
		break;
	case ENEMY_STATE::FALL:
		Fall();
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		AttackMove(player->GetLocation());
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

		if (hit_direction == STAGE_DIRECTION::TOP)
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


	//�v���C���[�������������ɂ�����
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE
		&& range <= DETECTION_DISTANCE_Y && range >= -DETECTION_DISTANCE_Y)
	{

		if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE
			&& range <= ATTACK_RANGE && range >= -ATTACK_RANGE)
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
			standby_time = PHYSICAL_STANDBY;
			physical_attack = true;

		}
		else
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = GHOST_ATTACK::MAGIC_ATTACK;
			standby_time = MAGIC_STANDBY;
			magic_attack = true;
			if (magic_time++ % 2 == 0)
			{
				//�e�̐���
				BulletManager::GetInstance()->CreateEnemyBullet
				(new GhostBullet(location, player_location));
			}
		}
	}

	else //�ʏ�ړ�
	{
		magic_attack = false;
		physical_attack = false;
		switch (action_type)
		{
		case GHOST_STATE::NORMAL:  //�ʏ�ړ�
			location.x -= speed;
			break;
		case GHOST_STATE::NORMAL_RIGHT://�E
			location.x += speed;
			break;
		default:
			break;
		}
	}

}

//-----------------------------------
//�U��
//-----------------------------------
void  EnemyGhost::Attack(Location player_location)
{

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


	DrawRotaGraphF(draw_location.x, draw_location.y, 1.4f,
		M_PI / 180, images[animation], TRUE);
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
		location.x += travel * speed;
		location.y += travel_y * speed;
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

	switch (bullet->GetAttribute()) //�󂯂��������̑���
	{
	case ATTRIBUTE::NORMAL:
		hp -= bullet->GetDamage() * 0; //����
		break;
	case ATTRIBUTE::EXPLOSION:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE; //��_����
		break;
	case ATTRIBUTE::MELT:
		hp -= bullet->GetDamage() * 0; //����
		break;
	case ATTRIBUTE::POISON:
		poison_damage = bullet->GetDamage() * 0; //����
		poison_time = bullet->GetDebuffTime() * 0; //����
		break;
	case ATTRIBUTE::PARALYSIS:
		paralysis_time = bullet->GetDebuffTime() * 0; //����
		paralysis_time = bullet->GetDamage() * 0; //����
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
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
	
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		//�A�j���[�V�����S�[�X�g
		if (animation_time++ % 10 == 0)
		{
			animation++;
		}

		if (animation > 5)
		{
			animation = 0;
		}
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
void EnemyGhost::DebugDraw()
{
	DrawRotaGraphF(location.x, location.y, 1.5f, M_PI / 180, images[animation], TRUE);

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xffffff, FALSE);
}
#endif //_DEBUG