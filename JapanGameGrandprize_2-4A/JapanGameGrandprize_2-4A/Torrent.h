#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

class Torrent :
    public EnemyBase
{
private:

public:

    //�R���X�g���N�^
    Torrent();

    //�f�X�g���N�^
    ~Torrent();

    //�X�V
    void Update(const class Player* player, const class Stage* stage) override;

    //�A�C�h�����
    void Idol() override;

    //�ړ�
    void Move(const Location player_location) override;

    //����
    void Fall() override;

    //�U��
    void  Attack(Location) override;

    //�U�����������Ă��邩
    AttackResource Hit() override;

    //���S
    void Death() override;

    //�v���C���[�̒e�Ƃ̓����蔻��
    void HitBullet(const BulletBase* bullet) override;

    //�`��
    void Draw() const override;

    //���W�̎擾
    Location GetLocation() const override;
};