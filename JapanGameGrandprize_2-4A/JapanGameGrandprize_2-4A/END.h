#pragma once
#include "AbstractScene.h"
#include <string>

class END :
    public AbstractScene
{
private:

    struct TOP_MENU
    {
        short number;
        std::string string;
    }top_menu[2];

    int select_menu;


    int menu_font;


    //�I��SE�p�T�E���h�n���h��
    int select_se;
    //����SE�p�T�E���h�n���h��
    int decision_se;
    
    //����Ԋu����
    int input_margin;
public:

    //�R���X�g���N�^
    END();

    //�f�X�g���N�^
    ~END();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
   
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};