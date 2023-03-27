#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

enum class TORRENT_ATTACK
{
    TACKLE = 0,     //�^�b�N��
    LEAF_CUTTER,    //�t���ς��΂�
    DROP_NUTS,      //�؂̎��𗎂Ƃ�
    NONE
};

class Torrent :
    public EnemyBase
{
private:
    bool attack; //�U��������������
    bool tackle_end; //�^�b�N�����I�����
    int tackle_end_point; //�^�b�N���̏I���n�_
    int shot_rate; //���@�e�̔��˃��[�g
    int attack_time; //�U�����Ă��鎞��
    int leaf_cutter_interval; //���̗t���ς��΂��U���Ɉڂ鎞��
    int drop_nuts_interval; //���̖؂̎��𗎂Ƃ��U���Ɉڂ鎞��
    int spawn_interval; //�؂̎��̐������鎞��
    int animation; //�A�j���[�V����
    int image_argument; //�摜�̈���

    TORRENT_ATTACK attack_state; //�U���̏��

private:
    //�t���ς̐���
    void CreateLeaf(Location);

    //�؂̎��̐���
    void CreateNuts();

    //�^�b�N���U��
    void Tackle();

    //�t���ς��΂��U��
    void LeafCutter(Location);

    //�؂̎��𗎂Ƃ��U��
    void DropNuts();

    // �U�����Ă��Ȃ�
    void AttackNone();
public:

    //�R���X�g���N�^
    Torrent(Location);

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

#ifdef _DEBUG
    //�X�V(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //�`��(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG
};