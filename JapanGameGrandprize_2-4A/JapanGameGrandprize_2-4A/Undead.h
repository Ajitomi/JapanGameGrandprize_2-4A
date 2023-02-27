#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Player.h"

class Undead :
    public EnemyBase, public BoxCollider
{
private:

    int damage; //�_���[�W
    int attack_interval; //���̍U���܂ł̎���
    int image; //�摜
    int attack_time; //�U�����Ă��鎞��(�f�o�b�O�p)
private:

    //�v���C���[�Ƃ̋���
    void DistancePlayer(const Location player_location);
public:

    //�R���X�g���N�^
    Undead();

    //�f�X�g���N�^
    ~Undead();

    //�`��ȊO�̍X�V
    void Update() override;

    //�A�C�h�����
    void Idol() override;

    //�ړ�
   void Move(const Location player_location) override;

    //�U��
    AttackResource Attack(const BoxCollider* collider) override;

    //���S
    void Death() override;

    //�v���C���[�̒e�Ƃ̓����蔻��
    bool HitBullet(const BulletBase* bullet) override;

    //�`��
    void Draw() const override;

    //���W�̎擾
    Location GetLocation() const override;
};