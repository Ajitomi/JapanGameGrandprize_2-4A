#pragma once
#include"EnemyBulletBase.h"

#define DRAGON_BULLET_IMAGES_NUM (10)
#define DRAGON_BULLET_IMAGE_SIZE (192)
#define DRAGON_BULLET_IMAGE_CENTER (96)

class DragonBullet :
    public EnemyBulletBase
{

    float direction; //�i�s����
    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h

    static int images[DRAGON_BULLET_IMAGES_NUM]; //�摜
    int frame_count;
    int images_index;

    static const float distance[DRAGON_BULLET_IMAGES_NUM];
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

