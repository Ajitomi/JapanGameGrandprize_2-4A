#include "EnemyGhost.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "BulletManager.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 75
#define GHOST_SIZE_Y 80

//�v���C���[��������
#define GHOST_DETECTION_DISTANCE 500

//�����U���͈�
#define GHOST_ATTACK_RANGE 20

//���@�U���͈�	
#define GHOST_ATTACK_MAGIC 400

//���@�U���������̍d������
#define GHOST_MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define GHOST_PHYSICAL_STANDBY 300

//�ړ��X�s�[�h
#define GHOST_SPEED 1.5

//�U���X�s�[�h
#define ATTACK_SPEED 4.5

//�h���b�v��(�ŏ�)
#define GHOST_MIN_DROP 1

//�h���b�v��(�ő�)
#define GHOST_DROP 7

//�S�[�X�g�̍U����
#define GHOST_ATTACK_DAMAGE 10


//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost(Location spawn_location)
{
	can_delete = false;
	left_move = true;
	attack = false;

	animation = 0;
	animation_time = 0;
	magic_time = 1;
	magic_num = 0;
	physical_time = 0;
	hp = 10;
	location = spawn_location;
	location.y = 120; //�e�X�g
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

	LoadDivGraph("Images/Enemy/ghostimages2.png", 5, 5, 1, 75, 80, ghost_image);
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

	if (animation_time++%5==0)
	{
		animation++;
	}

	if (animation > 4)
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
		Location chip_location = hit_stage.chip->GetLocation();
		Area chip_area = hit_stage.chip->GetArea();
		if ((chip_location.y + chip_area.height / 2) < (location.y + area.height / 2))
		{
			location = old_location;
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
	GhostMove(player_location);

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //�ʏ�ړ�
		location.x -= speed;
		break;
	case GHOST_STATE::NORMAL_RIGHT://�E
		location.x += speed;
		break;
	case GHOST_STATE::LEFT_lOWER:  //������ڎw��
		location.x -= speed;
		location.y += speed;
		break;
	case GHOST_STATE::LEFT_UPPER:  //�����ڎw��
		location.x -= speed;
		location.y -= speed;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //�E����ڎw��
		location.x += speed;
		location.y += speed;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //�E���ڎw���B
		location.x += speed;
		location.y -= speed;
		break;
	default:
		break;
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
		ret.damage = GHOST_ATTACK_DAMAGE;
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

	DrawRotaGraphF(draw_location.x, draw_location.y, 1.5f, M_PI / 180, ghost_image[animation], TRUE);
}

//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(const Location player_location)
{
	float range; //�v���C���[�Ƃ̋���	

	range = fabsf(location.x - player_location.x);

	//�v���C���[�������������ɂ�����
	if (range <= GHOST_DETECTION_DISTANCE && range >= -GHOST_DETECTION_DISTANCE)
	{
		if (location.x > player_location.x) //���Ɉړ�
		{
			if (player_location.y > location.y)
			{
				action_type = GHOST_STATE::LEFT_lOWER;
			}
			else
			{
				action_type = GHOST_STATE::LEFT_UPPER;
			}
		}
		else //�E�Ɉړ�
		{
			if (location.y + 10 >= player_location.y && location.y - 10 <= player_location.y)
			{
				action_type = GHOST_STATE::NORMAL_RIGHT;
			}
			if (player_location.y > location.y)
			{
				action_type = GHOST_STATE::RIGHT_LOWER;
			}
			else
			{
				action_type = GHOST_STATE::RIGHT_UPPER;
			}
		}
	}

	else //�ʏ�ړ�
	{
		action_type = GHOST_STATE::NORMAL;
		magic_attack = false;
		physical_attack = false;
	}

	////�U���͈͓��ɂ���ꍇ
	//if ((range <= GHOST_ATTACK_RANGE) && (!physical_attack))
	//{
	//	state = ENEMY_STATE::ATTACK;
	//	attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
	//	standby_time = GHOST_PHYSICAL_STANDBY;
	//	physical_attack = true;
	//}
	//else if ((range <= GHOST_ATTACK_MAGIC) && (!magic_attack))
	//{
	//	state = ENEMY_STATE::ATTACK;
	//	attack_state = GHOST_ATTACK::MAGIC_ATTACK;
	//	standby_time = GHOST_MAGIC_STANDBY;
	//	magic_attack = true;
	//	if (magic_time++ % 3 == 0)
	//	{
	//		//�e�̐���
	//		BulletManager::GetInstance()->CreateEnemyBullet
	//		(new GhostBullet(location, player_location));
	//	}
	//}
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