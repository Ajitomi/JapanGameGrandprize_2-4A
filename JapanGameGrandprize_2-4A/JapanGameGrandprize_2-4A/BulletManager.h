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

    EnemyBulletBase** enemy_bullets; //�G�̒e
    EnemyBulletBase** enemy_nuts; //�؂̎�
    int enemy_bullet_count; //�e�̐�����
    int enemy_nuts_count; //�؂̎��̐�����
    int enemy_bullet_max; //�e�̐����\��
    int enemy_nuts_max; //�؂̎��̐����\��
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

    //�؂̎��̐���
    void CreateEnemyNuts(class EnemyBulletBase* nuts);

    //�؂̎��̕��בւ�
    void SortEnemyNuts(const int nuts_num);

    //�؂̎��̍폜
    void DeleteEnemyNuts(const EnemyBulletBase* nuts);

    //�U������������
    AttackResource HitEnemyBullet(const int i);

    //�U������������
    AttackResource HitEnemyNuts(const int i);

    //�`��
    void Draw() const;

    //�e�̎擾
    EnemyBulletBase** GetEnemyBullets() const;

    //�e�̍ő�l�̎擾
    int EnemyGetBulletMax() const;

    //�؂̎��̎擾
    EnemyBulletBase** GetEnemyNuts() const;

    //�؂̎��̍ő�l�̎擾
    int EnemyGetNutsMax() const;
};