#pragma once
#include"EnemyBulletBase.h"

#define DRAGON_BULLET_IMAGES_NUM 10

class DragonBullet :
    public EnemyBulletBase
{

    float direction; //�i�s����
    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h

    static int images[DRAGON_BULLET_IMAGES_NUM]; //�摜
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

