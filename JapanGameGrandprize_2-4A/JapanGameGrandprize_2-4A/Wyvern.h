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
    int damage; //�_���[�W
    int bless_interval;         //���̃u���X�U���܂ł̎���
    int triple_bless_interval;  //����3�A�u���X�U���܂ł̎���
    int assault_interval;       //���̋��P�U���܂ł̎���
    int shot_rate;  //�u���X�̔��˃��[�g
    int assault_speed[2];   //���P�U���̃X�s�[�h(0 : X , 1 : Y)
    int image_argument; //�摜�̈���

    WYVERN_ATTACK attack_state; //�U��
private:

    //�ړ����̃A�j���[�V����
    void MoveAnimation();

    //�u���X�̐���
    void CreateBless(const Location);

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

