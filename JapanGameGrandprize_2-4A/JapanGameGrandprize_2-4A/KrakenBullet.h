#pragma once
#include "EnemyBulletBase.h"
class KrakenBullet :
    public EnemyBulletBase
{
    int image; //�摜

    float x_speed; //X�̃X�s�[�h
    float y_speed; //Y�̃X�s�[�h

    int game_tiem; //���ԑ��� 
    int start_time;//�U���J�n�𑪂鎞�� 

    bool start_attack; //�U���J�n�i�e�������n�߂�j

public:

    //�R���X�^���N�^
    KrakenBullet(Location, Location);

    //�f�X�g���N�^
    ~KrakenBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};

