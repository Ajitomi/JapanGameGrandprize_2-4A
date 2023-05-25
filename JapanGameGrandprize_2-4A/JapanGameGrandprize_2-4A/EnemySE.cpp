#include "EnemySE.h"
#include "DxLib.h"


NomalEnemySE EnemySE::slime_se = { 0,0 };  //�X���C��SE
NomalEnemySE EnemySE::undead_se = { 0,0 }; //�A���f�b�gSE
NomalEnemySE EnemySE::harpy_se = { 0,0 }; //�n�[�s�BSE
NomalEnemySE EnemySE::mage_se = { 0,0 }; //���C�WSE
NomalEnemySE EnemySE::ghost_se = { 0,0 }; //�S�[�X�gSE
NomalEnemySE EnemySE::wyvern_se = { 0,0 }; //���C�o�[��SE
LastBossSE EnemySE::last_boss_se = {};

int EnemySE::down_se = 0;		//�_�E����SE
int EnemySE::explosion_se = 0;	//explosion��eSE
int EnemySE::melt_se = 0;		//melt��eSE
int EnemySE::poison_se = 0;		//poison��eSE
int EnemySE::paralyze_se = 0;	//paralyze��eSE

EnemySE::~EnemySE()
{
	
}

//-----------------------------------
//�T�E���h�̓ǂݍ���
//-----------------------------------
void EnemySE::LoadSound()
{
	slime_se.attack = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/slimeattack.wav");
	undead_se.attack = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/undeadattack.wav");
	wyvern_se.attack = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/wyvernbreath.wav");
	last_boss_se.punch = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/LastBossPunch.wav");

	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	explosion_se = LoadSoundMem("Sounds/SE/Stage/PlayerShot/explosion.wav",8);
	melt_se = LoadSoundMem("Sounds/SE/Stage/PlayerShot/melt.wav",8);
	poison_se = LoadSoundMem("Sounds/SE/Stage/PlayerShot/poison.wav",8);
	paralyze_se = LoadSoundMem("Sounds/SE/Stage/PlayerShot/paralyze.wav",8);
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
}

//-----------------------------------
//�T�E���h�̍폜
//-----------------------------------
void EnemySE::DeleteSound()
{
	DeleteSoundMem(slime_se.attack);
	DeleteSoundMem(undead_se.attack);
	DeleteSoundMem(wyvern_se.attack);
	DeleteSoundMem(last_boss_se.punch);
}

//-----------------------------------
//���ʂ̐ݒ�
//-----------------------------------
void EnemySE::ChangeSoundVolume(const float volume)
{
	ChangeVolumeSoundMem(255 * (volume / 100), slime_se.attack);
	ChangeVolumeSoundMem(255 * (volume / 100), undead_se.attack);
	ChangeVolumeSoundMem(255 * (volume / 100), wyvern_se.attack);

}

//-----------------------------------
//�ʏ�G�l�~�[��SE�̎擾
//-----------------------------------
NomalEnemySE EnemySE::GetEnemySE(const ENEMY_KIND kind)
{
	NomalEnemySE ret = {};
	switch (kind)
	{
	case ENEMY_KIND::SLIME:
		ret = slime_se;
		break;
	case ENEMY_KIND::UNDEAD:
		ret = undead_se;
		break;
	case ENEMY_KIND::HARPY:
		break;
	case ENEMY_KIND::MAGE:
		break;
	case ENEMY_KIND::GHOST:
		break;
	case ENEMY_KIND::WYVERN:
		ret = wyvern_se;
		break;
	case ENEMY_KIND::SLIME_BOSS:
	case ENEMY_KIND::TORRENT:
	case ENEMY_KIND::KRAKEN:
	case ENEMY_KIND::DRAGON:
	case ENEMY_KIND::LAST_BOSS:
	case ENEMY_KIND::NONE:
		break;
	default:
		break;
	}

	return ret;
}

//-----------------------------------------------
// ��e����SE�̎擾
//-----------------------------------------------
int EnemySE::GetBulletSE(const ATTRIBUTE attribute)
{
	int return_se = 0;

	switch (attribute)
	{
	case ATTRIBUTE::NORMAL:
		;
		break;

	case ATTRIBUTE::EXPLOSION:
		return_se = explosion_se;
		break;

	case ATTRIBUTE::MELT:
		return_se = melt_se;
		break;

	case ATTRIBUTE::POISON:
		return_se = poison_se;
		break;

	case ATTRIBUTE::PARALYSIS:
		return_se = paralyze_se;
		break;

	case ATTRIBUTE::HEAL:
		;
		break;

	default:
		;
		break;
	}


	return return_se;
}

//���X�{�X��SE�̎擾
LastBossSE EnemySE::GetLastBossSE()
{
	return last_boss_se;
}