#pragma once
#include "EnemyBulletBase.h"
class KrakenBullet :
    public EnemyBulletBase
{
    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
public:

    //�R���X�^���N�^
    KrakenBullet(Location, Location);

    //�f�X�g���N�^
    ~KrakenBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};

