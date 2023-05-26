#include "GameMain.h"
#include "DxLib.h"
#include "../CameraWork.h"
#include "../PadInput.h"
#include "../Undead.h"
#include "../EnemySlime.h"
#include "../EnemyGhost.h"
#include "../Harpy.h"
#include "../BULLET.h"
#include "../Mage.h"
#include "../Wyvern.h"
#include "../Torrent.h"
#include "../EnemySlimeBoss.h"
#include "../Kraken.h"
#include"../Dragon.h"
#include"../Kraken.h"
#include "../LastBoss.h"
#include "DotByDot.h"
#include <math.h>
#include "GameMain_Restart.h"
#include "GameOver.h"
#include "GameClear.h"
#include "Title.h"
#include "End.h"

bool GameMain::is_help_mode = false;
//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain(short stage_num, unsigned int element_volume[PLAYER_ELEMENT], Pouch* pouch)
{
	this->stage_num = stage_num;

#undef DOT_BY_DOT

	char dis_stage_se[30];

	sprintf_s(dis_stage_se, sizeof(dis_stage_se), "Sounds/BGM/stage%d.wav", this->stage_num);

	if ((background_music = LoadSoundMem(dis_stage_se)) == -1) {
		background_music = LoadSoundMem("Sounds/BGM/stage1.wav");
		if (background_music == -1) {
			throw dis_stage_se;
		}
	}
	

	if ((help_image[0] = LoadGraph("Images/Help/Normal_Help.png")) == -1)
	{
		throw "images/help/Normal_Help.png";
	}

	if ((help_image[1] = LoadGraph("images/help/PouchOpen_Help.png")) == -1)
	{
		throw "images/help/PouchOpen_Help.png";
	}


	pause = new Pause();

	enemy_spawn_volume = 0;

	stage = new Stage(this->stage_num);

	player = new Player(stage, element_volume, pouch);

	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		old_element_volume[i] = element_volume[i];
	}

	stage->SetPlayer(player);

	EnemyBase::CreateLogFont();

	SpawnEnemy();

	stage->SetEnemy(enemy);
	stage->InitStage();
	stage->SetElement();

	camera_work = new CameraWork(0, 0, player, stage, this->stage_num);

	stage->SetCameraWork(camera_work);
	item_controller = ItemController::GetInstance();

	bullet_manager = BulletManager::GetInstance();

	input_margin = 0;
	is_spawn_boss = false;
	delay_animation_count = 0;

	ChangeVolumeSoundMem(200, background_music);
	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

	old_chemical_bullets[0] = *pouch->GetExplosion();
	old_chemical_bullets[1] = *pouch->GetMelt();
	old_chemical_bullets[2] = *pouch->GetPoison();
	old_chemical_bullets[3] = *pouch->GetPararysis();
	old_chemical_bullets[4] = *pouch->GetHeal();

	is_clear = false;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
GameMain::~GameMain()
{

	StopSoundMem(background_music);
	DeleteSoundMem(background_music);

	delete camera_work;
#ifdef _DEBUG

#else
	delete pause;
#endif
	delete player;
	delete stage;

	EnemyBase::DeleteLogFont();
	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		delete enemy[i];
	}
	delete[] enemy;

	EnemyBase::DeleteImage();

	delete item_controller;
	delete bullet_manager;
}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* GameMain::Update()
{
	stage->UpdateStageBackground(is_spawn_boss);

	pause->Update(stage_num);
		
	if (pause->IsPause() == TRUE) {

		short next_scene = pause->GetNextScene();

		if (next_scene == -1) { return this; }

		int now_graph = MakeGraph(1280, 720);

		Pause::MENU current_selection = static_cast<Pause::MENU>(next_scene);
		switch (current_selection)
		{
		case Pause::MENU::RETRY:
			
			GetDrawScreenGraph(0, 0, 1280, 720, now_graph);

			Pouch* pouch;
			pouch = player->GetPouch();
			for (int i = 0; i < BULLET_KINDS; i++)
			{
				pouch->SetChemicalBullets(old_chemical_bullets[i]);
			}

			return new GameMain_Restart(stage_num, now_graph, old_element_volume,pouch);
			break;

		case Pause::MENU::TITLE:
			SetHelpMode(false);
			return new Title();
			break;

		default:
			printfDx("�������ȋ@�\�ł��B\n");
			break;
		}
		return this;
	}




#ifdef _DEBUG
	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		return new DotByDot();
	}*/
#endif

	if(!is_help_mode)camera_work->Update();

	if (player->GetState() != PLAYER_STATE::DEATH && is_clear == false)
	{
		player->Update();
	}
	
	stage->Update(player);
	EnemyUpdate();

	// �{�X��|�����ꍇ
	if (is_clear == true)
	{
		ElementItem** element = player->GetPlayerElement();
		unsigned int element_volume[PLAYER_ELEMENT] = { 0 };
		for (int i = 0; i < PLAYER_ELEMENT; i++)
		{
			element_volume[i] = element[i]->GetVolume();
		}
		


		// �Ō�̃X�e�[�W���N���A�����ꍇ
		if (stage_num == 4) { return new End(); }
		if (DelayAnimation(DELAY_ANIMATION_TYPE::FADE_IN, 180.0f) == true) {
			return new GameClear(stage_num, element_volume, player->GetPouch());
		}
	}

	item_controller->Update(player);

	if (player->GetState() == PLAYER_STATE::DEATH)
	{
		if (DelayAnimation(DELAY_ANIMATION_TYPE::FADE_OUT, 120.0f) == true)
		{
			Pouch* pouch;
			pouch = player->GetPouch();
			for (int i = 0; i < BULLET_KINDS; i++)
			{
				pouch->SetChemicalBullets(old_chemical_bullets[i]);
			}

			return new GameOver(stage_num, old_element_volume, pouch);
		}
		
	}

	return this;
}

//-----------------------------------
//�G�l�~�[�̐���
//-----------------------------------
void GameMain::SpawnEnemy()
{

	vector<ENEMY_LOCATION> spawn;
	spawn = stage->GetEnemy_SpawnLocation();
	
	enemy_spawn_volume = spawn.size();
	enemy = new EnemyBase * [enemy_spawn_volume];
	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		enemy[i] = nullptr;
	}

	int i;
	for (i = 0; i < enemy_spawn_volume; i++)
	{
		switch (static_cast<ENEMY_KIND>(spawn[i].id))
		{
		case ENEMY_KIND::SLIME: //�X���C���̐���
			enemy[i] = new EnemySlime(spawn[i].location);
			break;

		case ENEMY_KIND::UNDEAD:	//�A���f�b�g�̐���
			enemy[i] = new Undead(spawn[i].location);
			break;

		case ENEMY_KIND::HARPY:		//�n�[�s�[�̐���
			enemy[i] = new Harpy(spawn[i].location);
			break;

		case ENEMY_KIND::MAGE:		//���C�W�̐���
			enemy[i] = new Mage(spawn[i].location);
			break;

		case ENEMY_KIND::GHOST:		//�S�[�X�g�̐���
			enemy[i] = new EnemyGhost(spawn[i].location);
			break;

		case ENEMY_KIND::WYVERN:	//���C�o�[���̐���
			enemy[i] = new Wyvern(spawn[i].location);
			break;

		case ENEMY_KIND::NONE:
			enemy[i] = nullptr;
			break;
		default:
			break;
		}
	}
}

//-----------------------------------
// �G�l�~�[�̍X�V����
//-----------------------------------
void GameMain::EnemyUpdate()
{
	vector<ENEMY_LOCATION> spawn;
	spawn = stage->GetEnemy_SpawnLocation();

	BulletBase** player_bullet;
	player_bullet = player->GetBullet();

	//�{�X��|�����ہA�v���C���[�̒e���폜	
	if (is_clear == true)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (player_bullet[i] != nullptr)
			{
				delete player_bullet[i];
				player_bullet[i] = nullptr;
				player->SortBullet(i);
				i--;
				if (i < 0)
				{
					break;
				}
			}
		}
	}

	//�X�e�[�W���ɐ������Ă���G�̐�
	short enemy_count = 0;

	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		//�v���C���[���{�X�G���A�ɓ������ہA�{�X���o��������
		if (camera_work->GetCameraLock() == true && is_spawn_boss == false)
		{
			if (static_cast<short>(ENEMY_KIND::SLIME_BOSS) <= spawn[i].id)
			{
				if (enemy[i] == nullptr)
				{
					switch (static_cast<ENEMY_KIND>(spawn[i].id))
					{
						//�X���C���{�X�̐���
					case ENEMY_KIND::SLIME_BOSS:
						enemy[i] = new EnemySlimeBoss(spawn[i].location);
						is_spawn_boss = true;
						break;

						//�g�����g�{�X�̐���
					case ENEMY_KIND::TORRENT:
						enemy[i] = new Torrent(spawn[i].location);
						is_spawn_boss = true;
						break;

						//�h���S���{�X�̐���
					case ENEMY_KIND::DRAGON:
						enemy[i] = new Dragon(spawn[i].location);
						is_spawn_boss = true;
						break;

					case ENEMY_KIND::LAST_BOSS:
						enemy[i] = new LastBoss(spawn[i].location);
						is_spawn_boss = true;
						break;

					default:
						break;
					}

				}
			}
		}

		if (enemy[i] != nullptr)
		{
			
			//�{�X�����ɓ������ہA�{�X�ȊO�̓G���폜
			if (is_spawn_boss == true && enemy[i]->GetEnemyKind() < ENEMY_KIND::SLIME_BOSS)
			{
				delete enemy[i];
				enemy[i] = nullptr;
				i--;
				break;
			}

			enemy[i]->Update(player, stage);

			//�G�l�~�[�̍U��

			if (enemy[i]->GetEnemyKind() == ENEMY_KIND::LAST_BOSS)
			{
				LastBoss* last_boss;
				last_boss = dynamic_cast<LastBoss*>(enemy[i]);

				player->HpDamage(last_boss->Hit(player));
			}
			else
			{
				if (enemy[i]->GetState() == ENEMY_STATE::ATTACK)
				{
					if (player->HitBox(enemy[i]))
					{
						player->HpDamage(enemy[i]->Hit());
					}
				}
			}

			//�v���C���[�̒e�Ƃ̓����蔻��
			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (player_bullet[j] == nullptr)
				{
					break;
				}

				if (enemy[i]->GetEnemyKind() == ENEMY_KIND::LAST_BOSS)
				{
					LastBoss* last_boss;
					last_boss = dynamic_cast<LastBoss*>(enemy[i]);

					if (last_boss->CheckHitBullet(player_bullet[j]))
					{
						player_bullet[j]->SetDeleteFlag(last_boss->GetLocation());
					}
				}
				else
				{
					if (enemy[i]->HitSphere(player_bullet[j]))
					{
						enemy[i]->HitBullet(player_bullet[j]);
						player_bullet[j]->SetDeleteFlag(enemy[i]->GetLocation());
					}
				}
			}

			//�G�l�~�[�̍폜
			if (enemy[i]->GetCanDelete() || (enemy[i]->GetLocation().x + enemy[i]->GetArea().width < 0 && enemy[i]->GetEnemyKind() != ENEMY_KIND::WYVERN))
			{
				if (ENEMY_KIND::SLIME_BOSS <= enemy[i]->GetEnemyKind())
				{
					is_clear = true;
				}

				//�G�l�~�[���X�e�[�W���Ŏ��񂾂�A�C�e���𐶐�
				if (0 <= enemy[i]->GetLocation().x + enemy[i]->GetArea().width)
				{
					item_controller->SpawnItem(enemy[i]);
				}
				delete enemy[i];
				enemy[i] = nullptr;
				i--;
			}
		}
	}

	bullet_manager->Update(stage);

	EnemyBulletBase** enemy_bullet;
	enemy_bullet = bullet_manager->GetEnemyBullets();

	//�G�̒e�ƃv���C���[�Ƃ̓����蔻��
	if (enemy_bullet != nullptr)
	{
		//�{�X���|�ꂽ���ʓ��ɂ���e���폜
		
		for (int i = 0; i < bullet_manager->EnemyGetBulletMax(); i++)
		{
			if (enemy_bullet[i] == nullptr)
			{
				break;
			}
			else if (is_clear == true)
			{
				bullet_manager->DeleteEnemyBullet(enemy_bullet[i]);
				i--;
				continue;
			}
			if (enemy_bullet[i]->HitBox(player))
			{
				player->HpDamage(bullet_manager->HitEnemyBullet(i));
				bullet_manager->DeleteEnemyBullet(enemy_bullet[i]);
				i--;
			}
		}
	}

	EnemyBulletBase** enemy_nuts;
	enemy_nuts = bullet_manager->GetEnemyNuts();

	if (enemy_nuts != nullptr) //�؂̎��Ƃ̓����蔻��
	{
		for (int i = 0; i < bullet_manager->EnemyGetNutsMax(); i++)
		{
			if (enemy_nuts[i] == nullptr)
			{
				break;
			}
			else if (is_clear == true)
			{
				bullet_manager->DeleteEnemyNuts(enemy_nuts[i]);
				i--;
				if (i < 0)
				{
					break;
				}
				continue;
			}

			if (enemy_nuts[i]->HitBox(player))
			{
				player->HpDamage(bullet_manager->HitEnemyNuts(i));
				bullet_manager->DeleteEnemyNuts(enemy_nuts[i]);
				i--;
				if (i < 0)
				{
					break;
				}
			}

			if (enemy_nuts[i] == nullptr)
			{
				break;
			}

			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (player_bullet[j] == nullptr)
				{
					break;
				}

				if (player_bullet[j]->HitSphere(enemy_nuts[i]))
				{
					player_bullet[j]->SetDeleteFlag(enemy_nuts[i]->GetLocation());

					bullet_manager->DeleteEnemyNuts(enemy_nuts[i]);
					i--;

					if (i < 0)
					{
						break;
					}
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

	//�X�e�[�W�̕`��
	stage->DrawStageBackground();

	if (is_help_mode)
	{
		if (player->GetIsPouchOpen())
		{
			DrawGraph(0, 0, help_image[1], TRUE);
		}
		else
		{
			DrawGraph(240, 0, help_image[0], TRUE);
		}
	}

	stage->Draw();
	stage->DrawObject();

	item_controller->Draw();

	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	player->Draw();

	
	bullet_manager->Draw();

	player->PouchDraw();

	//�|�[�Y		�`��
	if (pause->IsPause() == true) { pause->Draw(); }


}

void GameMain::SetHelpMode(bool is_help)
{
	is_help_mode = is_help;
	camera_work->SetCameraLock(is_help);
	camera_work->SetCameraState(CameraWork::STATE::FIXED);
}

bool GameMain::DelayAnimation(DELAY_ANIMATION_TYPE type, float time)
{
	//�A�j���[�V�����̒x��
	if (delay_animation_count < static_cast<int>(time))
	{
		int bright;
		switch (type)
		{
		case GameMain::DELAY_ANIMATION_TYPE::FADE_IN:
			// �t�F�[�h�C��
			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * 255));
			SetDrawBlendMode(DX_BLENDMODE_ADD_X4, bright);
			//DrawBox(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
			break;
		case GameMain::DELAY_ANIMATION_TYPE::FADE_OUT:
			// �t�F�[�h�A�E�g
			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * -255) + 255);
			SetDrawBright(bright, bright, bright);
			break;
		default:
			break;
		}
		
		delay_animation_count++;
		return false;
	}
	else
	{
		delay_animation_count = 0;
		return true;
	}

	return false;
}
