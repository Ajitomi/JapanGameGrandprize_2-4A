#pragma once
#include "AbstractScene.h"

//�^�C�g�����j���[
enum class TITLE_MENU
{
  
};

class Title :
    public AbstractScene
    
{
private:
    

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

