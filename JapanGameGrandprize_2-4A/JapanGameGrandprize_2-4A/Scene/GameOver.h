#pragma once
#include "AbstractScene.h"

class Pouch;

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

    //�v���C���[�������f
    unsigned int old_element_volume[7];

    //�X�e�[�W�J�n���̃v���C���[�|�[�`
    Pouch* old_pouch;

public:
    //�R���X�g���N�^
    GameOver(short stage_num, unsigned int old_element_volume[7], Pouch* old_pouch);

    //�f�X�g���N�^
    ~GameOver();

    //�X�V
    AbstractScene* Update() override;

    //�`��
    void Draw() const override;
};

