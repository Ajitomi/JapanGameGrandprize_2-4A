#include "BulletManager.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
BulletManager::BulletManager()
{
    enemy_bullets = nullptr;
    enemy_bullet_count = 0;
    enemy_bullet_max = 0;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
BulletManager::~BulletManager()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void BulletManager::Update()
{

}



//-----------------------------------
//�e�̐���
//-----------------------------------
void BulletManager::CreateEnemyBullet(class EnemyBulletsBase* bullet)
{

}

//-----------------------------------
//�e�̕��בւ�
//-----------------------------------
void BulletManager::SortEnemyBullet(int bullet_num)
{
    //�e�̒��g���\�[�g����
    for (int i = bullet_num + 1; i < enemy_bullet_max; i++)
    {
        if ((enemy_bullets[i] == nullptr))
        {
            break;
        }

        enemy_bullets[i - 1] = enemy_bullets[i];
        enemy_bullets[i] = nullptr;
    }
}

//-----------------------------------
//�e�̍폜
//-----------------------------------
EnemyBulletsBase** BulletManager::DeletePlayerBullet(EnemyBulletsBase* bullet)
{
    for (int i = 0; i < enemy_bullet_max; i++)
    {
        if (enemy_bullets[i] == bullet)
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
        }
    }
}

//-----------------------------------
// �`��
//-----------------------------------
void BulletManager::Draw()
{

}

//-----------------------------------
//�e�̎擾
//-----------------------------------
EnemyBulletsBase** BulletManager::GetPlayerBullets()
{
    return enemy_bullets;
}
