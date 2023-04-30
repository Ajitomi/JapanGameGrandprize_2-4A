#pragma once
#include "AbstractScene.h"
class GameOver :
	public AbstractScene
{
private:
    // �t�H���g�n���h��
    int menu_font;

    enum class MENU
    {
        RETRY,
        TITLE,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "RETRY",
        "TITLE"
    };

    // �I�����Ă��郁�j���[
    int select_menu;

    //����Ԋu����
    int input_margin;

    //�t�F�[�h�p�J�E���^
    int fade_counter;

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

