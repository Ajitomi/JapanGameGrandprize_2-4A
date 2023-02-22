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
	enemy = new EnemyGhost();
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
	if (enemy != nullptr)
	{
		enemy->Update();

		switch (enemy->GetEnemyKind())
		{
		case ENEMY_KIND::SLIME:		//�X���C��
		{			
			EnemySlime* slime;
			slime = dynamic_cast<EnemySlime*>(enemy);
			slime->HitPlayer(player);
			slime->AttackJudgement(player);
			break;
		}
		case ENEMY_KIND::UNDEAD:	//�A���f�b�g
		{
			Undead* undead;
			undead = dynamic_cast<Undead*>(enemy);
			if (undead->GetState() == UNDEAD_STATE::ATTACK)
			{
				if (undead->HitBox(player))
				{

				}
			}

			if (undead->GetCanDelete()) //���S
			{
				item_controller->SpawnItem(undead, undead->GetLocation());
				delete undead;
				enemy = nullptr;
			}
			break;
		}
		case ENEMY_KIND::HARPY:		//�n�[�s�B
		{
			break;
		}
		case ENEMY_KIND::MAGE:		//���C�W
		{
			break;
		}
		case ENEMY_KIND::GHOST:		//�S�[�X�g
		{
			EnemyGhost* ghost;
			ghost = dynamic_cast<EnemyGhost*>(enemy);
			ghost->GhostMove(player);

			if (ghost->GetCanDelete()) //���S
			{
				item_controller->SpawnItem(ghost, ghost->GetLocation());
				delete ghost;
				enemy = nullptr;
			}
			break;
		}
		case ENEMY_KIND::WYVERN:	//���C�o�[��
		{
			break;
		}
		case ENEMY_KIND::KING_SLIME://�X���C���L���O
		{
			break;
		}
		case ENEMY_KIND::TORRENT:	//�g�����g
		{
			break;
		}
		case ENEMY_KIND::GARGOYLE:	//�K�[�S�C��
		{
			break;
		}
		case ENEMY_KIND::DRAGON:	//�h���S��
		{
			break;
		}
		case ENEMY_KIND::END_BOSS:	//���X�{�X
		{
			break;
		}
		case ENEMY_KIND::NONE:
			break;
		default:
			break;
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
	if (enemy != nullptr)
	{
		enemy->Draw();
	}
}