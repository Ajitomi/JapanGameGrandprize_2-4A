#pragma once
#include "../Stage.h"

class Stage_Element :
    public Stage
{
private:

protected:

    //�A�j���[�V�����p�^�C�}�[
    float animation_timer;


public:
    Stage_Element();
    ~Stage_Element();
    virtual void Update() = 0;
    virtual void Draw() const = 0;
};