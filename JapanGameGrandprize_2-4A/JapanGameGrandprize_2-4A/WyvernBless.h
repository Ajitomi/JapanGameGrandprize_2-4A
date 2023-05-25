#pragma once
#include "EnemyBulletBase.h"
#define WYVERN_BLESS_EXTEND_RATE (0.2f)
#define WYVERN_IMAGES_NUM (9)
class WyvernBless :
    public EnemyBulletBase
{
private:
    //�ړ��p�ϐ�
    float x_speed;      //X�̃X�s�[�h
    float y_speed;      //Y�̃X�s�[�h
    double direction;    //�i�s����
    
    //�`��p�ϐ�
    int images[9];      //�摜
    int images_index;
    int frame_count;

public:

    //�R���X�g���N�^
    WyvernBless(const Location, const Location);

    //�f�X�g���N�^
    ~WyvernBless();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;

};

