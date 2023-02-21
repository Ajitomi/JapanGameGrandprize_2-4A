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
    int image; //�摜
    int attack_time; //�U�����Ă��鎞��(�f�o�b�O�p)
    ENEMY_TYPE attack_type; //�U���̑���
    UNDEAD_STATE state; //���

    Player* player; //�v���C���[
private:
    //�v���C���[�Ƃ̋���
    void DistancePlayer();
public:
    //�R���X�g���N�^
    Undead(Player* player);

    //�f�X�g���N�^
    ~Undead();

    //�`��ȊO�̍X�V
    void Update() override;

    //�v���C���[�̒e�Ƃ̓����蔻��
    void HitBullet(BulletBase* bullet) override;

    //�`��
    void Draw() const override;

    //��Ԃ̎擾
    UNDEAD_STATE GetState() const;
};

