#pragma once
#include "EnemyBulletBase.h"

class GhostBullet :
    public EnemyBulletBase
{
private:

    int image; //�摜

    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h

    //�G�t�F�N�g
    int tick;
    int frame;
    float angle;
public:

    //�R���X�g���N�^
    GhostBullet(const Location, const Location);

    //�f�X�g���N�^
    ~GhostBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};