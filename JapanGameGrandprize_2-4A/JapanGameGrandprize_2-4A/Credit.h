#pragma once
#include "Scene/AbstractScene.h"
class Credit :
    public AbstractScene
{
private:
    int display_time; //�\�����鎞��
    int time; //����
    unsigned int cr; //�F

public:

    //�R���X�g���N�^
    Credit();

    //�f�X�g���N�^
    ~Credit();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;

};

