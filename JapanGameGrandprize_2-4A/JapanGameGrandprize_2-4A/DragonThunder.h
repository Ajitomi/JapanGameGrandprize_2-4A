#pragma once
#include"EnemyBulletBase.h"

class DragonThunder :
    public EnemyBulletBase
{
    int image; //�摜
    int thunder_time; //�������ҋ@����
    bool attack; //�U���J�n
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

