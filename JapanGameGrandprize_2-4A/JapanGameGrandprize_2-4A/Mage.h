#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "EnemyBulletBase.h"

#define MAGE_BULLET_MAX 5

class Mage :
    public EnemyBase
{
private:
    bool can_teleport; //�e���|�[�g�\��
    int teleport_count; //�e���|�[�g����܂ł̎���
    int teleport_rate; //�e���|�[�g�̃��[�g
    int shot_rate; //���@�e�̔��˃��[�g
    int shot_count; //���˂����e�̐�
    int image; //�摜
    int drop; //�h���b�v����A�C�e���̎�ނ̐�
    int attack_interval; //�U���̊Ԋu

private:
    //�e���|�[�g
    void Teleport(const class Stage* stage);

    //�e�̐���
    void CreateBullet(Location);

public:

    //�R���X�g���N�^
    Mage(Location);

    //�f�X�g���N�^
    ~Mage();

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

#ifdef _DEBUG
    //�X�V(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //�`��(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG
};