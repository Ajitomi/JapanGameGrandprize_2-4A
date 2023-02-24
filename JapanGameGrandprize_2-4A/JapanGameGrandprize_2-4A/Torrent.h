#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

class Torrent :
    public EnemyBase,public BoxCollider
{
private:

public:
    //�R���X�g���N�^
    Torrent();

    //�f�X�g���N�^
    ~Torrent();

    //�X�V
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

