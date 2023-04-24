#pragma once
#include "EnemyBase.h"


enum class HAND_MOVE
{
    UP_DOWN = 0, //�㉺�ړ�
    CIRCULAR_MOTION, //�~��ړ�
    NONE
};

class LastBossHand :
    public EnemyBase
{
private:

    bool punch;  //�p���`���Ă���
    bool left_hand; //true:����,false:�E��
    bool attack; //�U��������������
    int move_volume; //�ړ���
    int angle; //�p�x
    int radius; //���a
    int attack_interval; //���̍U���܂ł̎���
    int punch_standby_time; //�p���`����܂ł̎���
    int animation; //�A�j���[�V����
    int image_argument; //�摜�̈���
    int death_time; //����ł��鎞��

    Location spawn_location; //�����n�_
    Location punch_start; //�p���`���n�߂��̍��W

    HAND_MOVE move; //�ړ����@

    HitMapChip hit_block; //�u���b�N�Ƃ̓����蔻��
private:

    //�e���|�[�g
    void Teleport(const class Stage* stage);

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

    //HP�o�[�̕\��
    void DrawHPBar(const int)const override;

    //���W�̎擾
    Location GetLocation() const override;

#ifdef _DEBUG
    //�X�V(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //�`��(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG

};

