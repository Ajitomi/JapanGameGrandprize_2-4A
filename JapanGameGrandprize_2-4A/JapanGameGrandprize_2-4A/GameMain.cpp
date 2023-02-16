#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"
#include "Item.h"
#include"EnemyGhost.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
	enemy = new Undead(player);
	camera_work = new CameraWork(0, 0, player, stage);
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

	return this;
}

//-----------------------------------
// �G�l�~�[�̍X�V����
//-----------------------------------
void GameMain::EnemyUpdate()
{
	//Item** drop_item; //�h���b�v�A�C�e��
	enemy->Update();

		switch (enemy->GetEnemyKind())
		{
		case ENEMY_KIND::SLIME:		//�X���C��
			break;
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
}