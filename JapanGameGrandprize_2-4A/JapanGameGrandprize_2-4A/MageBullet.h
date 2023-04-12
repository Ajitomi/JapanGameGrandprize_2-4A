#pragma once
#include "EnemyBulletBase.h"

class MageBullet :
    public EnemyBulletBase
{
private:

    int image; //�摜
    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
public:

    //�R���X�g���N�^
    MageBullet(const ENEMY_TYPE , const Location , const Location);

    //�f�X�g���N�^
    ~MageBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override ;
};