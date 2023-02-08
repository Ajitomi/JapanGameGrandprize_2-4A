#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"

enum class UNDEAD_STATE
{
    IDOL,   //�A�C�h�����
    MOVE,   //�ړ�
    ATTACK, //�U��
    DEATH,  //���S
};

class Undead :
    public EnemyBase
{
private:
    int damage; //�_���[�W
    Location location; //���S���W
    UNDEAD_STATE state; //���
    BoxCollider collider; //�����蔻��
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

    //�`��
    void Draw() const override;
};

