#pragma once
#include"EnemyBulletBase.h"

#define LOCATION_DATA 60

class SlimeBossThunder :
    public EnemyBulletBase
{
    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h

    int color;

    bool left_move;
    int orientation_time;
    int data_switch;


    int old_radius[LOCATION_DATA];
    Location old_location[LOCATION_DATA];

public:

    //�R���X�^���N�^
    SlimeBossThunder(Location, Location);

    //�f�X�g���N�^
    ~SlimeBossThunder();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};