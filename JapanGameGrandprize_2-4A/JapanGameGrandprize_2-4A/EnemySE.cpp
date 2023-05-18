#include "EnemySE.h"
#include "DxLib.h"


NomalEnemySE EnemySE::slime_se = { 0,0 };  //�X���C��SE
NomalEnemySE EnemySE::undead_se = { 0,0 }; //�A���f�b�gSE
NomalEnemySE EnemySE::harpy_se = { 0,0 }; //�n�[�s�BSE
NomalEnemySE EnemySE::mage_se = { 0,0 }; //���C�WSE
NomalEnemySE EnemySE::ghost_se = { 0,0 }; //�S�[�X�gSE
NomalEnemySE EnemySE::wyvern_se = { 0,0 }; //���C�o�[��SE

int EnemySE::down_se = 0; //�_�E����SE

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
	wyvern_se.attack = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/wyvernbless.wav");
}

//-----------------------------------
//�T�E���h�̍폜
//-----------------------------------
void EnemySE::DeleteSound()
{
	DeleteSoundMem(slime_se.attack);
	DeleteSoundMem(undead_se.attack);
	DeleteSoundMem(wyvern_se.attack);
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
