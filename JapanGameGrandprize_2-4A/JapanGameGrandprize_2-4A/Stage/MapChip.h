#pragma once
#include "../BoxCollider.h"
#include <Windows.h>

#define MAP_CHIP_SIZE 40.f
class Player;

class MapChip :
    public BoxCollider
{
private:
    //�������Ă������
    //���v����[1:��, 2:�E, 3:��, 4:��]
    POINT collision_dir;


public:
    //�R���X�g���N�^
    MapChip();
    //�R���X�g���N�^
    MapChip(short id, const int* p_image, Location location, Area area);
    //�f�X�g���N�^
    ~MapChip();
    //�X�V
    void Update(Player* player);
    //�`��
    virtual void Draw() const;

    const char* GetName() { return class_name; }

    const POINT GetMapChip_Collision() { 
        
        POINT w = collision_dir;
   
        collision_dir = { 0,0 };

        return w;
        //short w = collision_dir; collision_dir = 0; return w; 

    }

protected:
    const char* class_name = "default";
    int image;
    Area image_size;
    float ex_rate;
    
};