#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"
#include"EnemySlime.h"
#include"EnemyGhost.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{
	stage = new Stage();
	player = new Player(stage);
	enemy = new EnemyBase * [3];
	enemy[0] = new Undead();
	enemy[1] = new EnemySlime();
	enemy[2] = new EnemyGhost();
	camera_work = new CameraWork(0, 0, player, stage);
	item_controller = new ItemController();

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
}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* GameMain::Update()
{
#ifdef _DEBUG
	//�V�[���؂�ւ��e�X�g		�f�o�b�N
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) && input_margin >= 30)
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
	stage->Update(player);

	EnemyUpdate();
	item_controller->Update(player);

	return this;
}

//-----------------------------------
// �G�l�~�[�̍X�V����
//-----------------------------------
void GameMain::EnemyUpdate()
{
	for (int i = 0; i < 3; i++)
	{

		if (enemy[i] != nullptr)
		{
			enemy[i]->Update();

			switch (enemy[i]->GetState())
			{
			case ENEMY_STATE::IDOL:
				enemy[i]->Idol();
				break;
			case ENEMY_STATE::MOVE:
				enemy[i]->Move(player->GetLocation());
				break;
			case ENEMY_STATE::ATTACK:
				enemy[i]->Attack(player);
				break;
			case ENEMY_STATE::DEATH:
				enemy[i]->Death();
				break;
			default:
				break;
			}

			if (enemy[i]->GetCanDelete())
			{

			}

			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (player->GetBullet(j) != nullptr)
				{
					enemy[i]->HitBullet(player->GetBullet(j));
				}
			}
		}

	}

}

//-----------------------------------
// �`��
//-----------------------------------
void GameMain::Draw()const
{
	//�w�i
	SetBackgroundColor(149, 249, 253);

	item_controller->Draw();
	player->Draw();
	stage->Draw();
	for (int i = 0; i < 3; i++)
	{
		if (enemy != nullptr)
		{
			enemy[i]->Draw();
		}
	}
}