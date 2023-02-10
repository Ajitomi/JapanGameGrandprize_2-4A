#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
	camera_work = new CameraWork(0.0f,0.0f);

	input_margin = 0;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
GameMain::~GameMain()
{
	delete player;
	delete stage;
	delete camera_work;
}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* GameMain::Update()
{
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

	//printfDx("CameraX:%f\tCameraY:%f\n", camera_work->GetCamera().x, camera_work->GetCamera().y);
	camera_work->Update();
	player->Update();
	stage->Update();
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
}