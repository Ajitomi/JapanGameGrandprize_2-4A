#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Player.h"

enum class UNDEAD_STATE
{
    IDOL,   //�A�C�h�����
    MOVE,   //�ړ�
    ATTACK, //�U��
    DEATH,  //���S
};

class Undead :
    public EnemyBase, public BoxCollider
{
private:
    int damage; //�_���[�W
    int attack_interval; //���̍U���܂ł̎���
    int attack; //�U�����Ă���

    Location arm[2]; //�r�̓����蔻��
    ENEMY_TYPE attack_type; //�U���̑���
    UNDEAD_STATE state; //���
    LineCollider* collider; //�����蔻��
private:
    //�U��
    void Attack();

public:
    //�R���X�g���N�^
    Undead();

    //�f�X�g���N�^
    ~Undead();

    //�`��ȊO�̍X�V
    void Update() override;

    //�v���C���[�Ƃ̋���
    void DistancePlayer(Player* player);

    //�`��
    void Draw() const override;

    //LineCollider�̎擾
    LineCollider GetLineCollider() const;
};

