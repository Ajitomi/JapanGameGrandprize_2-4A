#pragma once
#include"EnemyBulletBase.h"

class DragonThunder :
    public EnemyBulletBase
{
    int image[20]; //�摜
    int thunder_time; //�������ҋ@����
    bool attack; //�U���J�n

    int tick;
    int phase;
    int frame;

public:

    //�R���X�^���N�^
    DragonThunder(float x,float y);

    //�f�X�g���N�^
    ~DragonThunder();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};

