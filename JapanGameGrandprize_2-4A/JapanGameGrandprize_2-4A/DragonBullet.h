#pragma once
#include"EnemyBulletBase.h"

class DragonBullet :
    public EnemyBulletBase
{
    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
public:

    //�R���X�^���N�^
    DragonBullet(Location, Location);

    //�f�X�g���N�^
    ~DragonBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};

