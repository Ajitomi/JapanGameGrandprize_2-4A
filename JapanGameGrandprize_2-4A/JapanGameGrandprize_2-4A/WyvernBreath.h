#pragma once
#include "EnemyBulletBase.h"
#define WYVERN_BREATH_EXTEND_RATE (0.2f)
#define WYVERN_IMAGES_NUM (9)
class WyvernBreath :
    public EnemyBulletBase
{
private:
    //�ړ��p�ϐ�
    float x_speed;      //X�̃X�s�[�h
    float y_speed;      //Y�̃X�s�[�h
    double direction;    //�i�s����
    
    //�`��p�ϐ�
    static int* images;      //�摜
    int images_index;
    int frame_count;

public:

    //�R���X�g���N�^
    WyvernBreath(const Location, const Location);

    //�f�X�g���N�^
    ~WyvernBreath();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;

    //�摜�̓ǂݍ���
    static void LoadImages();

    //�摜�̍폜
    static void DeleteImages();

};

