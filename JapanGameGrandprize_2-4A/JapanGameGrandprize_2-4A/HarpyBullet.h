#pragma once
#include"EnemyBulletBase.h"

class HarpyBullet :public EnemyBulletBase
{
private:

    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
public:

    //�R���X�^���N�^
    HarpyBullet(Location, Location);

    //�f�X�g���N�^
    ~HarpyBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};