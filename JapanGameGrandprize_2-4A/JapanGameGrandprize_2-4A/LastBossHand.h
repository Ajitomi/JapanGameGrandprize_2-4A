#pragma once
#include "EnemyBase.h"


class LastBossHand :
    public EnemyBase
{
private:

    bool punch;  //�p���`���Ă���
    bool attack; //�U��������������
    int attack_interval; //���̍U���܂ł̎���
    int animation; //�A�j���[�V����
    int image_argument; //�摜�̈���
private:

    //�p���`
    void Punch();

    //�ړ����̃A�j���[�V����
    void MoveAnimation();
public:

    //�R���X�g���N�^
    LastBossHand(const Location, const bool);

    //�f�X�g���N�^
    ~LastBossHand();

    //�X�V
    void Update(const class Player* player, const class Stage* stage) override;

    //�A�C�h�����
    void Idol() override;

    //�ړ�
    void Move(const Location player_location) override;

    //����
    void Fall() override;

    //�U��
    void  Attack(const Location) override;

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

#ifdef _DEBUG
    //�X�V(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //�`��(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG

};

