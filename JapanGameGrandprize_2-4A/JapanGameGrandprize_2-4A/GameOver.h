#pragma once
#include "AbstractScene.h"
class GameOver :
	public AbstractScene
{
private:

public:
    //�R���X�g���N�^
    GameOver(short stage_num);

    //�f�X�g���N�^
    ~GameOver();

    //�X�V
    AbstractScene* Update() override;

    //�`��
    void Draw() const override;
};

