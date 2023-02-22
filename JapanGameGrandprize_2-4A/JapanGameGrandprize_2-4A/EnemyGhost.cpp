#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//�v���C���[��������
#define DETECTION_DISTANCE 500

//�����U���͈�
#define ATTACK_RANGE 15

//���@�U���͈�	
#define ATTACK_MAGIC 400

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
	player_x = 0;
	player_y = 0;
	physical_attack = false;
	magic_attack = false;
	setting = false;
	kind = ENEMY_KIND::GHOST;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
}


//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
{
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::ATTACK:
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}
}

//�A�C�h�����
void EnemyGhost::Idol()
{

}

//�ړ�
void EnemyGhost::Move(const Location player_location)
{
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

		if (++standby_time % 300 == 0) //�d������
		{
			magic_attack = true;
			standby_time = 0;
		}
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		if (bullet->HitBox(collider))
		{
			ENEMY_TYPE attack_type[1] = { bullet->GetType() };
			ret.damage = bullet->GetDamage();
			ret.type = attack_type;
			ret.type_count = 1;
		}

		if (++standby_time % 60 == 0) //�d������
		{
			physical_attack = true;
			standby_time = 0;
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
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{
	//�X�N���[���ɍ��킹�ĕ`��
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	if (attack_state == GHOST_ATTACK::MAGIC_ATTACK) //���@�U���̃��[�V����
	{
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(128, 0, 0), TRUE);
	}
	else if (attack_state == GHOST_ATTACK::PHYSICAL_ATTACK) //�ڋߍU���̃��[�V����
	{
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
	}
}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(Player* player)
{
	int range; //�v���C���[�Ƃ̋���	
	
	range = location.x - player->GetLocation().x;

	//�v���C���[�������������ɂ�����
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (range > player->GetLocation().x) //���Ɉړ�
		{
			if (player->GetLocation().y > location.y)
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
			if (player->GetLocation().y > location.y)
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
	if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE && physical_attack == false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}
	else if (range <= ATTACK_MAGIC && range >= -ATTACK_MAGIC && magic_attack == false)
	{
		player_x = player->GetLocation().x;
		player_y = player->GetLocation().y;
		action_type = GHOST_STATE::MAGIC_ATTACK;
	}

	if (HitBox(player) != false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}



}

//-----------------------------------
// �v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void EnemyGhost::HitBullet(BulletBase* bullet)
{

}



