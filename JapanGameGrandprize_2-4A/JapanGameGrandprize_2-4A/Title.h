#pragma once
#include "AbstractScene.h"



class Title :
    public AbstractScene
    
{
private:

    //�^�C�g�����j���[
    enum class TITLE_MENU
    {
        PLAY,
        OPTION,
        HELP,
        END
    };

    //�w�i�p�O���t�B�b�N�n���h��
    int background_image;

    //�^�C�g�����p�t�H���g�n���h��
    int title_font;

    //BGM�p�T�E���h�n���h��
    int bgm;

    //�I��SE�p�T�E���h�n���h��
    int select_se;
    //����SE�p�T�E���h�n���h��
    int decision_se;
    

public:
    //�R���X�g���N�^
    Title();

    //�f�X�g���N�^
    ~Title();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
   
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

