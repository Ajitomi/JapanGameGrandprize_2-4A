#pragma once
#include "AbstractScene.h"
#include <string>

class END :
    public AbstractScene
{
private:

    enum class MENU
    {
        TITLE,
        EXIT,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "TITLE",
        "EXIT"
    };

    // �I�����Ă��郁�j���[
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