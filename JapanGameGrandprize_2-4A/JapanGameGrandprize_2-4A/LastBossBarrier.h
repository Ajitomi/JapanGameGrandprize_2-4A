#pragma once
#include "SphereCollider.h"

//�o���A�̗�
#define BARRIER_VOLUME 5

class LastBossBarrier :
    public SphereCollider
{
private:
    bool end_deployment; //�o���A�̓W�J�I��
    int* images; //�摜
    int count; //�J�E���g
    int animation[BARRIER_VOLUME]; //�A�j���[�V����
    double size; //�傫��
    double angle; //�p�x
    int durability; //�ϋv�l
    int old_durability; //�O��̑ϋv�l
    int volume; //���ꂽ�o���A�̗�

private:

    //�o���A�̓W�J
    void Deployment();
public:
    //�R���X�g���N�^
    LastBossBarrier(const Location);

    //�f�X�g���N�^
    ~LastBossBarrier();

    //�X�V
    void Update();

    //�v���C���[�̒e�Ƃ̓����蔻��
    void HitBullet(const class BulletBase* bullet);

    //�`��
    void Draw() const;

    //�ϋv�l�o�[�̕`��
    void DrawDurabilityBar() const;

    //�j�󂳂ꂽ
    bool Break() const;
};

