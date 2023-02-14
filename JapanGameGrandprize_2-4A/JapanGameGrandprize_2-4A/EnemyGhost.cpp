#include "EnemyGhost.h"
#include"DxLib.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//�v���C���[��������
#define DETECTION_DISTANCE 200
//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	ghost_death = false;
	ghost_vanish = false;  
	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	action_time = 0;
	action_type = 0;
}


//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
{
	switch (action_type)
	{
	case 0:  //�ʏ�ړ�
		location.x--; 
		break;
	case 1:  //������ڎw��
		location.x--;
		location.y++;
		break;
	case 2:  //�����ڎw��
		location.x--;
		location.y--;
		break;
	case 3:  //�E����ڎw��
		location.x++;
		location.y++;
		break;
	case 4:  //�E���ڎw���B
		location.x++;
		location.y--;
		break;
	}
	

}

//-----------------------------------
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{
	DrawFormatString(60, 60, GetColor(255, 0, 0), "%d", action_time);
	DrawBox(location.x, location.y, location.x + GHOST_SIZE_X, location.y + GHOST_SIZE_Y, GetColor(255,0,0), TRUE);
}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(Player*player)
{
	int range; //�v���C���[�Ƃ̋���
	action_time= location.x - player->GetLocationX();
	range = location.x - player->GetLocationX();

	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (location.x > player->GetLocationX())
		{
			if (player->GetLocationY() > location.y)
			{
				action_type = 1;
			}
			else
			{
				action_type = 2;
			}
		}
		else
		{
			if (player->GetLocationY() > location.y)
			{
				action_type = 3;
			}
			else
			{
				action_type = 4;
			}
		}
	}
	else
	{
		action_type = 0;
	}
	

}


//-----------------------------------
// �S�[�X�g�̍U������
//-----------------------------------
void EnemyGhost::GhostAttack()
{

}

//-----------------------------------
// �v���C���[�Ƃ̋���
//-----------------------------------
bool EnemyGhost::GhostRange()
{
	return true;
}