#pragma once
#include "EnemyBulletBase.h"

class BulletManager
{
    // �V���O���g��
private:
    //�R���X�g���N�^
    BulletManager();
    static BulletManager* instance; //�C���X�^���X

public:
    //�C���X�^���X�̎擾
    static BulletManager* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new BulletManager();
        }

        return instance;
    }
    // �V���O���g���@�����܂�

private:
    class EnemyBulletsBase** enemy_bullets;
    int enemy_bullet_count;
    int enemy_bullet_max;

public:
    //�f�X�g���N�^
    ~BulletManager();

    //�X�V
    void Update();

    //�e�̐���
    void CreateEnemyBullet(class EnemyBulletsBase* bullet);

    //�e�̕��בւ�
    void SortEnemyBullet(int bullet_num);

    //�e�̍폜
    EnemyBulletsBase** DeletePlayerBullet(EnemyBulletsBase* bullet);

    //�`��
    void Draw();

    //�e�̎擾
    EnemyBulletsBase** GetPlayerBullets();

};

