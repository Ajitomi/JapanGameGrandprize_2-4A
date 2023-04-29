#pragma once
#include "AbstractScene.h"
#include "Define.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Stage/Element/Stage_Element.h"


class DotByDot :
    public AbstractScene
{
private:
    int font;
    int state;
    EnemyBase** enemy;
    Player* player;
    Stage_Element* element;



    const char str[5][10] = { "idol","move","fall","attack","death" };
public:
    //�R���X�g���N�^
    DotByDot();

    //�f�X�g���N�^
    ~DotByDot();

    //�X�V
    AbstractScene* Update() override;

    //�`��
    void Draw() const override;
};

