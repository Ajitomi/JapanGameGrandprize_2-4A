#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f

class MapChip :
    public BoxCollider
{
private:
    int image;
    Area image_size;
    float ex_rate;
public:
    //�R���X�g���N�^
    MapChip();
    //�R���X�g���N�^
    MapChip(const int* p_image, Location location, Area area);
    //�f�X�g���N�^
    ~MapChip();
    //�X�V
    virtual void Update();
    //�`��
    virtual void Draw() const;

protected:

};