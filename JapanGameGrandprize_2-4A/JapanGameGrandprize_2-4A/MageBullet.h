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
    MageBullet(ENEMY_TYPE ,Location , Location);

    //�f�X�g���N�^
    ~MageBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override ;
};