#pragma once
#include "EnemyBulletBase.h"
class KrakenBreath :
    public EnemyBulletBase
{
    int image; //�摜

    float x_speed; //X�̃X�s�[�h
    float y_speed; //Y�̃X�s�[�h


public:

    //�R���X�^���N�^
    KrakenBreath(Location, Location);

    //�f�X�g���N�^
    ~KrakenBreath();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};

