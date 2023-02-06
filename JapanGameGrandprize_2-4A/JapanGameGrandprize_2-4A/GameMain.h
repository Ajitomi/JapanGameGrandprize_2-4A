#pragma once
#include "AbstractScene.h"
#include "Stage.h"

class GameMain :
    public AbstractScene
{
private:
    //stage�I�u�W�F�N�g
    Stage* stage;

public:
    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

