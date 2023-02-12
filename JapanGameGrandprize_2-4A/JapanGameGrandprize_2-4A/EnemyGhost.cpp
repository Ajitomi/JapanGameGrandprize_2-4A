#include "EnemyGhost.h"
#include"DxLib.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE 20

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	ghost_death = false;
	ghost_vanish = false;  
	ghost_x = 600;
	ghost_y = 400;
	action_time = 0;
	action_type = 0;
	action_type = 0;

}


//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
{

	GhostMove();
	GhostAttack();

}

//-----------------------------------
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{
	DrawBox(ghost_x, ghost_y, ghost_x + GHOST_SIZE, ghost_y + GHOST_SIZE, 0x00ff00, TRUE);
}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove()
{

	if (action_time++ % 120 == 0) {
		action_type = GetRand(3);
	}
	switch (action_type)
	{
	case 0:
		ghost_x++;
		ghost_y--;
		break;
	case 1:
		ghost_x--;
		ghost_y++;
		break;
	case 2:
		ghost_x++;
		break;
	case 3:
		ghost_x--;
		break;
	}

}


//-----------------------------------
// �S�[�X�g�̍U������
//-----------------------------------
void EnemyGhost::GhostAttack()
{



}