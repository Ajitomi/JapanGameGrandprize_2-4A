#pragma once
#include"EnemyBulletBase.h"




class HarpyBullet :public EnemyBulletBase
{
private:

    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h

      //�G�t�F�N�g
    int Tick;
    int frame;
    int PHASE;
    float angle;
    bool display_permit;

public:

    //�R���X�^���N�^
    HarpyBullet(const Location, const Location);

    //�f�X�g���N�^
    ~HarpyBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};