#pragma once
#include "EnemyBase.h"

enum class LAST_BOSS_ATTACK
{
    MAGIC = 0,  //���@�U��
    PUNCH,      //�p���`
    SWORD,      //���ł̍U��
    DEATHBLO,   //�K�E
    NONE
};

class LastBoss :
    public EnemyBase
{
private:
    bool down; //�_�E��
    bool attack; //�U��������������
    int down_time; //�_�E�����Ă��鎞��
    int attack_interval; //���̍U���܂ł̎���
    int animation; //�A�j���[�V����
    int image_argument; //�摜�̈���
    int attack_time; //�U�����Ă��鎞��(�f�o�b�O�p)
    EnemyBase** hand; //��

    HitMapChip hit_stage; //�X�e�[�W�Ƃ̓����蔻��

    LAST_BOSS_ATTACK attack_state; //�U��
private:

    //�ړ����̃A�j���[�V����
    void MoveAnimation();

    //�_�E������̕��A
    bool Revival();

    //�p���`����
    void Punch();

    //�U�����Ȃ�
    void AttackNone();
public:

    //�R���X�g���N�^
    LastBoss(Location);

    //�f�X�g���N�^
    ~LastBoss();

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

    //�v���C���[�̒e�Ƃ̓����蔻��
    bool CheckHitBulelt(const BulletBase* bullet);

    //�v���C���[�ƃp���`�Ƃ̓����蔻��
    AttackResource PunchAttack(const BoxCollider*);

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