#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f
class Player;

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
    void Update(Player* player);
    //�`��
    virtual void Draw() const;

    const char* GetName() { return class_name; }

protected:
    const char* class_name = "default";
    int image;
    Area image_size;
    float ex_rate;
    
};