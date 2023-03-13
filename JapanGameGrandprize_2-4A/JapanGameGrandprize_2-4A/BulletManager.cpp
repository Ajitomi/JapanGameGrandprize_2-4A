#include "BulletManager.h"
#include "Stage/Stage.h"
#include "CameraWork.h"

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
void BulletManager::Update(const Stage* stage)
{
    for (int i = 0; i < enemy_bullet_count; i++)
    {
        if (enemy_bullets[i] == nullptr)
        {
            break;
        }

        enemy_bullets[i]->Update();

        if (enemy_bullets[i]->ScreenOut() || enemy_bullets[i]->HitStage(stage)) //��ʊO�ɏo����
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
            enemy_bullet_count--;
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
        if (enemy_bullets == nullptr)
        {
            //�ő�l�̍X�V
            enemy_bullet_max += ENEMY_BULLET_EXPANSION;

            enemy_bullets = new EnemyBulletBase * [enemy_bullet_max];
            for (int i = 0; i < enemy_bullet_max; i++)
            {
                enemy_bullets[i] = nullptr;
            }
        }
        else
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
            for (int i = enemy_bullet_count; i < enemy_bullet_max; i++)
            {
                enemy_bullets[i] = nullptr;
            }
        }
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
    }
}

//-----------------------------------
//�e�̍폜
//-----------------------------------
void BulletManager::DeleteEnemyBullet(const EnemyBulletBase* bullet)
{
    for (int i = 0; i < enemy_bullet_max; i++)
    {
        if (enemy_bullets[i] == bullet)
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
            enemy_bullet_count--;
            break;
        }
    }
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource BulletManager::Hit(const int i)
{
    AttackResource ret = { 0,nullptr,0 }; //�߂�l

    ENEMY_TYPE attack_type[1] = { enemy_bullets[i]->GetType() };
    ret.damage = enemy_bullets[i]->GetDamage();
    ret.type = attack_type;
    ret.type_count = 1;

    return ret;
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

//-----------------------------------
//�e�̍ő�l�̎擾
//-----------------------------------
int BulletManager::EnemyGetBulletMax() const
{
    return enemy_bullet_max;
}