#pragma once
#include"EnemyBulletBase.h"

class SlimeBossBullet :
    public EnemyBulletBase
{
    int image[12]; //�摜
    int image_type;
    int image_change_time;
    int image_change_no;
    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
    int gravity_power;


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