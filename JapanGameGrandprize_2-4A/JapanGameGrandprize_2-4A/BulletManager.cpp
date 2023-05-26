#include "BulletManager.h"
#include "Stage/Stage.h"
#include "CameraWork.h"

BulletManager* BulletManager::instance = nullptr;

//�g����
#define ENEMY_BULLET_EXPANSION 10

//�؂̎��̊g����
#define NUTS_EXPANSION 5

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
BulletManager::BulletManager()
{

    enemy_bullets = nullptr;
    enemy_nuts = nullptr;
    enemy_bullet_count = 0;
    enemy_nuts_count = 0;
    enemy_bullet_max = 0;
    enemy_nuts_max = 0;
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

    for (int i = 0; i < enemy_nuts_max; i++)
    {
        delete enemy_nuts[i];
    }
    delete[] enemy_nuts;

    instance = nullptr;
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
            i--;
        }
    }

    for (int i = 0; i < enemy_nuts_count; i++)
    {
        if (enemy_nuts[i] == nullptr)
        {
            break;
        }

        enemy_nuts[i]->Update();

        if (enemy_nuts[i]->HitStage(stage)) //�X�e�[�W�ɂ�������
        {
            delete enemy_nuts[i];
            enemy_nuts[i] = nullptr;

            SortEnemyNuts(i);
            enemy_nuts_count--;
            i--;
        }
    }
}

//-----------------------------------
//�e�̐���
//-----------------------------------
void BulletManager::CreateEnemyBullet(class EnemyBulletBase* bullet)
{

    if (enemy_bullet_max <= enemy_bullet_count)
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
            for (int i = 0; i < enemy_bullet_max; i++)
            {
                if (i < enemy_bullet_count)
                {
                    enemy_bullets[i] = temporary_bullets[i];
                }
                else
                {
                    enemy_bullets[i] = nullptr;
                }
            }
            delete[] temporary_bullets;
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
//�؂̎��̐���
//-----------------------------------
void BulletManager::CreateEnemyNuts(class EnemyBulletBase* nuts)
{

    if (enemy_nuts_max <= enemy_nuts_count)
    {
        if (enemy_nuts == nullptr)
        {
            //�ő�l�̍X�V
            enemy_nuts_max += ENEMY_BULLET_EXPANSION;

            enemy_nuts = new EnemyBulletBase * [enemy_nuts_max];
            for (int i = 0; i < enemy_nuts_max; i++)
            {
                enemy_nuts[i] = nullptr;
            }
        }
        else
        {
            EnemyBulletBase** temporary_nuts; //���p

            //���
            temporary_nuts = enemy_nuts;

            //�ő�l�̍X�V
            enemy_nuts_max += ENEMY_BULLET_EXPANSION;

            //�e�̍Đ���
            enemy_nuts = new EnemyBulletBase * [enemy_nuts_max];

           //���Ă����e��߂�
            for (int i = 0; i < enemy_nuts_max; i++)
            {
                if (i < enemy_nuts_count)
                {
                    if (enemy_nuts[i] != nullptr)
                    {
                        enemy_nuts[i] = temporary_nuts[i];
                    }
                }
                else
                {
                    enemy_nuts[i] = nullptr;
                }
            }
            delete[] temporary_nuts;
        }
    }
    //�e�̐���
    enemy_nuts[enemy_nuts_count] = dynamic_cast<EnemyBulletBase*>(nuts);

    enemy_nuts_count++;
    PlayStreamSoundMem(EnemySE::GetTorrentSE().falling_nut_se, DX_PLAYTYPE_BACK);
}

//-----------------------------------
//�؂̎��̕��בւ�
//-----------------------------------
void BulletManager::SortEnemyNuts(const int nuts_num)
{

    //�e�̒��g���\�[�g����
    for (int i = nuts_num + 1; i < enemy_nuts_max; i++)
    {
        if ((enemy_nuts[i] == nullptr))
        {
            break;
        }

        enemy_nuts[i - 1] = enemy_nuts[i];
        enemy_nuts[i] = nullptr;
    }
}

//-----------------------------------
//�؂̎��̍폜
//-----------------------------------
void BulletManager::DeleteEnemyNuts(const EnemyBulletBase* nuts)
{

    for (int i = 0; i < enemy_nuts_max; i++)
    {
        if (enemy_nuts[i] == nuts)
        {
            PlaySoundMem(EnemySE::GetTorrentSE().break_nut_se, DX_PLAYTYPE_BACK);
            delete enemy_nuts[i];
            enemy_nuts[i] = nullptr;

            SortEnemyNuts(i);
            enemy_nuts_count--;
            break;
        }
    }
}
//-----------------------------------
//�U������������
//-----------------------------------
AttackResource BulletManager::HitEnemyBullet(const int i)
{

    AttackResource ret = { 0,nullptr,0 }; //�߂�l

    ENEMY_TYPE attack_type[1] = { enemy_bullets[i]->GetType() };
    ret.damage = enemy_bullets[i]->GetDamage();
    ret.type = attack_type;
    ret.type_count = 1;

    return ret;
}

//-----------------------------------
//�U������������
//-----------------------------------
AttackResource BulletManager::HitEnemyNuts(const int i)
{

    AttackResource ret = { 0,nullptr,0 }; //�߂�l

    ENEMY_TYPE attack_type[1] = { enemy_nuts[i]->GetType() };
    ret.damage = enemy_nuts[i]->GetDamage();
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

    for (int i = 0; i < enemy_nuts_count; i++)
    {
        if (enemy_nuts[i] == nullptr)
        {
            break;
        }

        enemy_nuts[i]->Draw();
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

//-----------------------------------
//�؂̎��̎擾
//-----------------------------------
EnemyBulletBase** BulletManager::GetEnemyNuts() const
{

    return enemy_nuts;
}

//-----------------------------------
//�؂̎��̍ő�l�̎擾
//-----------------------------------
int BulletManager::EnemyGetNutsMax() const
{

    return enemy_nuts_max;
}