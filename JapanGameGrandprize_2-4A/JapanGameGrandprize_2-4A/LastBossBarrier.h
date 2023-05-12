#pragma once
#include "SphereCollider.h"

class LastBossBarrier :
    public SphereCollider
{
private:
    int* images; //�摜
    int count; //�J�E���g
    int animation; //�A�j���[�V����
    double size; //�傫��
    double angle; //�p�x
    int durability; //�ϋv�l
    int old_durability; //�O��̑ϋv�l
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

