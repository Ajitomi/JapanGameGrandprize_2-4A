#pragma once
#include "EnemyKind.h"
#include "Define.h"

struct NomalEnemySE
{
    int move; //�ړ�
    int attack; //�U��
};

struct LastBossSE
{
    int punch;
    int special_attack[2];
};

class EnemySE
{
private:
   static NomalEnemySE slime_se;  //�X���C��SE
   static NomalEnemySE undead_se; //�A���f�b�gSE
   static NomalEnemySE harpy_se; //�n�[�s�BSE
   static NomalEnemySE mage_se; //���C�WSE
   static NomalEnemySE ghost_se; //�S�[�X�gSE
   static NomalEnemySE wyvern_se; //���C�o�[��SE
   static LastBossSE last_boss_se; //���X�{�XSE

   static int down_se; //�_�E����SE

   static int explosion_se; //explosion��eSE
   static int melt_se;      //melt��eSE
   static int poison_se;    //poison��eSE
   static int paralyze_se;  //paralyze��eSE

private:
    EnemySE() = default;

public:

	~EnemySE();

    //�T�E���h�̓ǂݍ���
    static void LoadSound();

    //�T�E���h�̍폜
    static void DeleteSound();

    //���ʂ̐ݒ�
    static void ChangeSoundVolume(const float);

    //�ʏ�G�l�~�[��SE�̎擾
    static NomalEnemySE GetEnemySE(const ENEMY_KIND);

    //���X�{�X��SE�̎擾
    static LastBossSE GetLastBossSE();

    static int GetBulletSE(const ATTRIBUTE);
};

