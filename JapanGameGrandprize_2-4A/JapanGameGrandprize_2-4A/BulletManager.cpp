#include "BulletManager.h"

BulletManager* BulletManager::instance = nullptr;

#define ENEMY_BULLET_EXPANSION 10
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
    for (int i = 0; i < enemy_bullet_max; i++)
    {
        delete enemy_bullets[i];
    }
    delete[] enemy_bullets;
}

//-----------------------------------
//�X�V
//-----------------------------------
void BulletManager::Update()
{
    for (int i = 0; i < enemy_bullet_count; i++)
    {
        if (enemy_bullets[i] == nullptr)
        {
            break;
        }

        enemy_bullets[i]->Update();

        if (enemy_bullets[i]->ScreenOut()) //��ʊO�ɏo����
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
        }
    }
}

//-----------------------------------
//�e�̐���
//-----------------------------------
void BulletManager::CreateEnemyBullet(class EnemyBulletBase* bullet)
{
    if (enemy_bullet_count == enemy_bullet_max)
    {
        EnemyBulletBase** temporary_bullets; //���p

        //���
        temporary_bullets = enemy_bullets;

        //�ő�l�̍X�V
        enemy_bullet_max += ENEMY_BULLET_EXPANSION;

        //�e�̍Đ���
        enemy_bullets = new EnemyBulletBase * [enemy_bullet_max];

        //���Ă����e��߂�
        enemy_bullets = temporary_bullets;

        delete[] temporary_bullets;
    }
    //�e�̐���
    enemy_bullets[enemy_bullet_count] = dynamic_cast<EnemyBulletBase*>(bullet);

    enemy_bullet_count++;

}

//-----------------------------------
//�e�̕��בւ�
//-----------------------------------
void BulletManager::SortEnemyBullet(const int bullet_num)
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
        enemy_bullet_count--;
    }
}

//-----------------------------------
//�e�̍폜
//-----------------------------------
void BulletManager::DeletePlayerBullet(const EnemyBulletBase* bullet)
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
void BulletManager::Draw() const
{
    for (int i = 0; i < enemy_bullet_count; i++)
    {
        if (enemy_bullets[i] == nullptr)
        {
            break;
        }

        enemy_bullets[i]->Draw();
    }
}

//-----------------------------------
//�e�̎擾
//-----------------------------------
EnemyBulletBase** BulletManager::GetEnemyBullets() const
{
    return enemy_bullets;
}
