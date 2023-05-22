#pragma once
#include "EnemyBase.h"


enum class WYVERN_ATTACK
{
    BLESS,          //�u���X
    TRIPLE_BRACE,   //3�A�u���X
    ASSAULT,        //���P�U��
    NONE
};

class Wyvern :
    public EnemyBase
{
private:
    bool attack_end; //�U�����I�����
    bool attack; //�U��������������
    bool now_assault; //���P�U�����ǂ���
    int animation; //�A�j���[�V����
    int attack_angle;           //�U�����̊p�x
    int attack_interval;        //���̍U���܂ł̎���
    int bless_wait_time;        //�u���X��ł܂ł̑ҋ@����
    int bless_interval;         //���̃u���X�U���܂ł̎���
    int triple_bless_interval;  //����3�A�u���X�U���܂ł̎���
    int assault_interval;       //���̋��P�U���܂ł̎���
    int assault_end_time;       //���P�U�����I���܂ł̎���
    int move_wait_time;         //�U�����I����Ĉړ�����܂ł̑ҋ@����
    int assault_hit_stage;      //���P���ɃX�e�[�W�ɂ���������
    int shot_rate;  //�u���X�̔��˃��[�g
    int shot_count; //���˂����e�̐�
    Location assault_start;     //���P�U���̃X�^�[�g�ʒu
    Location assault_speed;     //���P�U���̃X�s�[�h
    int image_argument; //�摜�̈���

    WYVERN_ATTACK attack_state; //�U��
    HitMapChip hit_stage;

private:

    //�ړ����̃A�j���[�V����
    void Animation();

    //�u���X
    void Bless(const Location);

    //�g���v���u���X
    void TripleBless(const Location);

    //���P�U��
    void Assault(const Location);

    // �U�����Ă��Ȃ�
    void AttackNone();
public:

    //�R���X�g���N�^
    Wyvern(Location);

    //�f�X�g���N�^
    ~Wyvern();

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