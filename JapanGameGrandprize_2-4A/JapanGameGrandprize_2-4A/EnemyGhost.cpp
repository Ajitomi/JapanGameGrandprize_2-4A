#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//�v���C���[��������
#define GHOST_DETECTION_DISTANCE 500

//�����U���͈�
#define GHOST_ATTACK_RANGE 15

//���@�U���͈�	
#define GHOST_ATTACK_MAGIC 400

//���@�U���������̍d������
#define GHOST_MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define GHOST_MAGIC_PHYSICAL 300

//�ړ��X�s�[�h
#define GHOST_SPEED 1.5

//�U���X�s�[�h
#define ATTACK_SPEED 4.5

//�S�[�X�g�̍U����
#define GHOST_ATTACK_DAMAGE 10

//������邱��
//�����蔻��A�A�C�e�������A�ڋߍU������ł����̂�

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	hp = 10;
	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	standby_time = 0;
	standby_count = 0;
	physical_attack = false;
	magic_attack = false;
	kind = ENEMY_KIND::GHOST;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = GHOST_STATE::NORMAL;
	bullet = nullptr;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
EnemyGhost::~EnemyGhost()
{
	delete bullet;
}

//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
{
	float screen_x; //��ʃX�N���[�����l������X���W

	screen_x = location.x - CameraWork::GetCamera().x;
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		if ((-area.width < screen_x) && (screen_x < SCREEN_WIDTH + area.width))
		{
			state = ENEMY_STATE::MOVE;
		}
		break;
	case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::ATTACK:
		switch (attack_state)
		{
		case GHOST_ATTACK::PHYSICAL_ATTACK:
			standby_count++;
			if (standby_count < GHOST_MAGIC_PHYSICAL) //�d������
			{
				physical_attack = true;
				standby_time = 0;
				attack_state = GHOST_ATTACK::NONE;
			}
			break;
		case GHOST_ATTACK::MAGIC_ATTACK:
			standby_count++;
			if (standby_time < GHOST_MAGIC_STANDBY) //�d������
			{
				magic_attack = true;
				standby_time = 0;
				attack_state = GHOST_ATTACK::NONE;
			}
			break;
		case GHOST_ATTACK::NONE:
			break;
		default:
			break;
		}
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	if (bullet != nullptr)
	{
		bullet->Update();
	}
}

//�A�C�h�����
void EnemyGhost::Idol()
{

}

//�ړ�
void EnemyGhost::Move(const Location player_location)
{
	GhostMove(player_location);

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //�ʏ�ړ�
		location.x -= GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_lOWER:  //������ڎw��
		location.x -= GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_UPPER:  //�����ڎw��
		location.x -= GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //�E����ڎw��
		location.x += GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //�E���ڎw���B
		location.x += GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	default:
		break;
	}
}

//-----------------------------------
//�U��
//-----------------------------------
AttackResource EnemyGhost::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	switch (attack_state)
	{
	case GHOST_ATTACK::PHYSICAL_ATTACK:
		if (HitBox(collider))
		{
			ENEMY_TYPE attack_type[1] = { *type };
			ret.damage = GHOST_ATTACK_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}

	
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		if (bullet != nullptr)
		{
			if (bullet->HitBox(collider))
			{
				ENEMY_TYPE attack_type[1] = { bullet->GetType() };
				ret.damage = bullet->GetDamage();
				ret.type = attack_type;
				ret.type_count = 1;
			}
		}
		break;
	case GHOST_ATTACK::NONE:
		break;
	default:
		break;
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void EnemyGhost::Death()
{

}

//-----------------------------------
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{
	//�X�N���[���ɍ��킹�ĕ`��
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	switch (attack_state)
	{
	case GHOST_ATTACK::PHYSICAL_ATTACK:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
		if (bullet != nullptr)
		{
			bullet->Draw();
		}
		break;
	case GHOST_ATTACK::NONE:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
		break;
	default:
		break;
	}
}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(const Location player_location)
{
	int range; //�v���C���[�Ƃ̋���	
	
	range = location.x - player_location.x;

	//�v���C���[�������������ɂ�����
	if (range <= GHOST_DETECTION_DISTANCE && range >= -GHOST_DETECTION_DISTANCE)
	{
		if (range > player_location.x) //���Ɉړ�
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
	}

	//�U���͈͓��ɂ���ꍇ
	if ((range <= GHOST_ATTACK_RANGE) && (range >= -GHOST_ATTACK_RANGE) && (!physical_attack))
	{
		attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
	}
	else if ((range <= GHOST_ATTACK_MAGIC) && (range >= -GHOST_ATTACK_MAGIC) && (!magic_attack))
	{
		attack_state = GHOST_ATTACK::MAGIC_ATTACK;
		if (bullet == nullptr)
		{
			bullet = new GhostBullet(location, player_location);
		}
	}
}

//-----------------------------------
// �v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void EnemyGhost::HitBullet(const BulletBase* bullet)
{

}



