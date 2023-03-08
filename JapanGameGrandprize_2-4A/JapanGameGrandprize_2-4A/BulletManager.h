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

    EnemyBulletBase** enemy_bullets;
    int enemy_bullet_count;
    int enemy_bullet_max;

public:
    //�f�X�g���N�^
    ~BulletManager();

    //�X�V
    void Update(const class Stage* stage);

    //�e�̐���
    void CreateEnemyBullet(class EnemyBulletBase* bullet);

    //�e�̕��בւ�
    void SortEnemyBullet(const int bullet_num);

    //�e�̍폜
    void DeleteEnemyBullet(const EnemyBulletBase* bullet);

    //�U�����������Ă��邩
    AttackResource Hit(const int i);

    //�`��
    void Draw() const;

    //�e�̎擾
    EnemyBulletBase** GetEnemyBullets() const;

    //�e�̍ő�l�̎擾
    int EnemyGetBulletMax() const;
};

