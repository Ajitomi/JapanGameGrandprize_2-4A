#pragma once
#include "EnemyBulletBase.h"
class WyvernBless :
    public EnemyBulletBase
{
private:

    int image; //�摜
    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
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

