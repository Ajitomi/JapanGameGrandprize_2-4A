#pragma once
#include "AbstractScene.h"
class GameClear :
    public AbstractScene
{
private:

public:
    //�R���X�g���N�^
    GameClear(short stage_num);

    //�f�X�g���N�^
    ~GameClear();

    //�X�V
    AbstractScene* Update() override;

    //�`��
    void Draw() const override;

};

