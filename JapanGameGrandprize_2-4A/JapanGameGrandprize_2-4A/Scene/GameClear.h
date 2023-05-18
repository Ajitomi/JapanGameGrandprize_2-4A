#pragma once
#include "AbstractScene.h"

class ElementItem;

class GameClear :
    public AbstractScene
{
private:
    // �t�H���g�n���h��
    int menu_font;

    //�v���C���[�̏������f
    unsigned int element_volume[7];

public:
    //�R���X�g���N�^
    GameClear(short stage_num, unsigned int element_volume[7]);

    //�f�X�g���N�^
    ~GameClear();

    //�X�V
    AbstractScene* Update() override;

    //�`��
    void Draw() const override;

};

