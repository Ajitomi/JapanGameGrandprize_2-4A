#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

enum class TORRENT_STATE
{
    IDOL,   //�A�C�h�����
    MOVE,   //�ړ�
    ATTACK, //�U��
    DEATH,  //���S
};
class Torrent :
    public EnemyBase,public BoxCollider
{
private:
    TORRENT_STATE state; //���

    Player* player; //�v���C���[

public:
    //�R���X�g���N�^
    Torrent(Player* player);

    //�f�X�g���N�^
    ~Torrent();

    //�X�V
    void Update() override;

    //�v���C���[�̒e�Ƃ̓����蔻��
    void HitBullet(BulletBase* bullet) override;

    //�`��
    void Draw() const override;

    //��Ԃ̎擾
    TORRENT_STATE GetState() const;
};

