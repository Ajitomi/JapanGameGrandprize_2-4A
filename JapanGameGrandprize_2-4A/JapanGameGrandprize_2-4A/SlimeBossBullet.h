#pragma once
#include"EnemyBulletBase.h"

class SlimeBossBullet :
    public EnemyBulletBase
{
    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
public:

    //�R���X�^���N�^
    SlimeBossBullet(Location, Location);

    //�f�X�g���N�^
    ~SlimeBossBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};