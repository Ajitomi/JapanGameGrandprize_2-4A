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
    virtual AbstractScene* Update() = 0;

    //�`��Ɋւ��邱�Ƃ�����
    virtual void Draw() const = 0;
};

