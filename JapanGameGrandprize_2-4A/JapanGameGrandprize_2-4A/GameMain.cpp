#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"

#define _DEBUG

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
	enemy = new Undead();
	ghost = new EnemyGhost();
	camera_work = new CameraWork(0,0);

	input_margin = 0;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
GameMain::~GameMain()
{
	delete player;
	delete stage;
	delete enemy;
	delete camera_work;
	delete ghost;
}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* GameMain::Update()
{
#ifdef _DEBUG
	//�V�[���؂�ւ��e�X�g		�f�o�b�N
	if (CheckHitKey(KEY_INPUT_Z) && input_margin >= 30) 
	{
		input_margin = 0;
		return new Title();
	}

	if (input_margin < 30) 
	{
		input_margin++;
	}
#endif

	camera_work->Update();
	player->Update();
	stage->Update();
	enemy->Update();
	ghost->Update();

	ghost->GhostMove(player);

	Undead* a = dynamic_cast<Undead*>(enemy);
	a->DistancePlayer(player);

	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void GameMain::Draw()const
{
	//�w�i
	SetBackgroundColor(149, 249, 253);

	player->Draw();
	stage->Draw();
	enemy->Draw();
	ghost->Draw();
}

