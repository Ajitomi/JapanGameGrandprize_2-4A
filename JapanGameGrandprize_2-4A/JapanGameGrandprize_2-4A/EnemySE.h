#pragma once
#include "EnemyKind.h"

struct NomalEnemySE
{
    int move; //�ړ�
    int attack; //�U��
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

   static int down_se; //�_�E����SE


private:
    EnemySE() = default;

public:

	~EnemySE();

    //�T�E���h�̓ǂݍ���
    static void LoadSound();

    //�T�E���h�̍폜
    static void DeleteSound();

    //�ʏ�G�l�~�[��SE�̎擾
    static NomalEnemySE GetEnemySE(const ENEMY_KIND);
};

