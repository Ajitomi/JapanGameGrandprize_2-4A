#include "EnemyGhost.h"
#include"DxLib.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//�v���C���[��������
#define DETECTION_DISTANCE 500

//�����U���͈�
#define ATTACK_RANGE 100

//���@�U���͈�	
#define ATTACK_MAGIC 400

//�ړ��X�s�[�h
#define GHOST_SPEED 1.5

//�U���X�s�[�h
#define ATTACK_SPEED 4.5


//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost()
{

	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	ghost_vanish = false;
	action_type = GHOST_STATE::NORMAL;
	kind = ENEMY_KIND::GHOST;
}


//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
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
	case GHOST_STATE::MAGIC_ATTACK: //���@�U��
		if (standby_time++ % 600 == 0)
		{
			magic_attack = true;
		}
		break;
	case GHOST_STATE::PHYSICAL_ATTACK:
		physical_attack = true;
		break;
	}

	GhostAttack(); //

}

//-----------------------------------
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{

	if (action_type == GHOST_STATE::MAGIC_ATTACK) //���@�U���̃��[�V����
	{
		DrawBox(location.x, location.y, location.x + GHOST_SIZE_X,
			location.y + GHOST_SIZE_Y, GetColor(0, 255, 0), TRUE);
	}
	else if (action_type == GHOST_STATE::PHYSICAL_ATTACK) //�ڋߍU���̃��[�V����
	{
		DrawBox(location.x, location.y, location.x + GHOST_SIZE_X,
			location.y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		DrawBox(location.x, location.y, location.x + GHOST_SIZE_X,
			location.y + GHOST_SIZE_Y, GetColor(255, 0, 255), TRUE);
	}


}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(Player* player)
{
	int range; //�v���C���[�Ƃ̋���
	range = location.x - player->GetLocationX();

	//�v���C���[�������������ɂ�����
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (location.x > player->GetLocationX()) //���Ɉړ�
		{
			if (player->GetLocationY() > location.y)
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
			if (player->GetLocationY() > location.y)
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
		action_type = GHOST_STATE::MAGIC_ATTACK;
	}
}


//-----------------------------------
// �S�[�X�g�̍U������
//-----------------------------------
void EnemyGhost::GhostAttack()
{
	if (magic_attack == true) //���@�U��
	{

	}

	if (physical_attack == true) //�����U��
	{

	}
}

void EnemyGhost::HitBullet(Bullet* bullet)
{

}