#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"
#include "MageBullet.h"

#define MAGE_BULLET_MAX 20

class Mage :
    public EnemyBase,public BoxCollider
{
private:
    int shot_rate; //���@�e�̔��˃��[�g
    int shot_count; //���˂����e�̐�
    int image; //�摜
    int drop; //�h���b�v����A�C�e���̎�ނ̐�
    Player* player; //�v���C���[

    MageBullet* bullet[20]; //�e

private:
    //�e�̐���
    void CreateBullet();

    //�e�̕��ёւ�
    void SortBullet(int);
public:

    //�R���X�g���N�^
    Mage();

    //�f�X�g���N�^
    ~Mage();

    //�X�V
    void Update() override;

    //�A�C�h�����
    void Idol() override;

    //�ړ�
    void Move(const Location player_location) override;

    //�U��
    void  Attack() override;

    //�U�����������Ă��邩
    AttackResource HitCheck(const BoxCollider* collider) override;

    //���S
    void Death() override;

    //�v���C���[�̒e�Ƃ̓����蔻��
    bool HitBullet(const BulletBase* bullet) override;

    //�`��
    void Draw() const override;

    //�e�̎擾
    MageBullet GetBullet(int) const;

    //���W�̎擾
    Location GetLocation() const override;
};

