#include "GameMain.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"
#include"EnemySlime.h"
#include"EnemyGhost.h"
#include"Harpy.h"
#include "BULLET.h"
#include "Mage.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{

	//�w�i�摜�ǂݍ���
	background_image = LoadGraph("Images/Scene/gamemain.png");

	stage = new Stage();
	player = new Player(stage);
	stage->SetPlayer(player);
	enemy = new EnemyBase * [4];
	enemy[0] = new EnemySlime();
	enemy[1] = new Undead();
	enemy[2] = new Harpy();//new EnemyGhost();
	enemy[3] = new Mage();
	camera_work = new CameraWork(0, 800, player, stage);
	item_controller = new ItemController();

	bullet_manager = BulletManager::GetInstance();

	input_margin = 0;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
GameMain::~GameMain()
{
	delete player;
	delete stage;

	for (int i = 0; i < 3; i++)
	{
		delete enemy[i];
	}

	delete[] enemy;
	delete camera_work;
	delete bullet_manager;
}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* GameMain::Update()
{
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
	BulletBase** player_bullet;
	player_bullet = player->GetBullet();

	bullet_manager->Update(stage);

	EnemyBulletBase** enemy_bullet;
	enemy_bullet = bullet_manager->GetEnemyBullets();

	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player,stage);

			//�G�l�~�[�̍U��
			if (enemy[i]->GetState() == ENEMY_STATE::ATTACK)
			{
				if (player->HitBox(enemy[i]))
				{
					player->HpDamage(enemy[i]->Hit());
				}
			}

			//�v���C���[�̒e�Ƃ̓����蔻��
			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (player_bullet[j] == nullptr)
				{
					break;
				}

				if (player_bullet[j]->HitBox(enemy[i]))
				{
					enemy[i]->HitBullet(player_bullet[j]);
					delete player_bullet[j];
					player_bullet[j] = nullptr;
					player->SortBullet(j);
				}
			}

			if (enemy[i]->GetCanDelete()) //�G�l�~�[�̍폜
			{
				item_controller->SpawnItem(enemy[i]);
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	//�G�̒e�ƃv���C���[�Ƃ̓����蔻��
	if (enemy_bullet != nullptr)
	{
		for (int i = 0; i < bullet_manager->EnemyGetBulletMax(); i++)
		{
			if (enemy_bullet[i] == nullptr)
			{
				break;
			}
			if (enemy_bullet[i]->HitBox(player))
			{
				player->HpDamage(bullet_manager->Hit(i));
				bullet_manager->DeleteEnemyBullet(enemy_bullet[i]);
				i--;
			}
		}
	}
}

//-----------------------------------
// �`��
//-----------------------------------
void GameMain::Draw()const
{
	SetBackgroundColor(149, 249, 253);
	//�w�i	�`��
	DrawGraph(0, 0, background_image, FALSE);

	stage->Draw();
	item_controller->Draw();

	player->Draw();

	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	bullet_manager->Draw();

}