#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "EnemyBulletBase.h"

#define MAGE_BULLET_MAX 5

class Mage :
    public EnemyBase,public BoxCollider
{
private:
    bool can_teleport; //�e���|�[�g�\��

    int shot_rate; //���@�e�̔��˃��[�g
    int shot_count; //���˂����e�̐�
    int image; //�摜
    int drop; //�h���b�v����A�C�e���̎�ނ̐�
    int attack_interval; //�U���̊Ԋu

private:
    //�e���|�[�g
    void Teleport();

    //�e�̐���
    void CreateBullet(Location);

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
    void  Attack(Location) override;

    //�U�����������Ă��邩
    AttackResource HitCheck(const BoxCollider* collider) override;

    //���S
    void Death() override;

    //�v���C���[�̒e�Ƃ̓����蔻��
    bool HitBullet(const BulletBase* bullet) override;

    //�`��
    void Draw() const override;

    //���W�̎擾
    Location GetLocation() const override;
};

