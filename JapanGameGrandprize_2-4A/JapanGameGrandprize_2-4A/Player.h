#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "BULLET.h"

#define GRAVITY 10

class Player : public BoxCollider
{
private:
	int image;						//�摜�p�ϐ�
	int image_size_x, image_size_y; //�摜�̃T�C�Y
	int bullet_count;				//�������e�̐�
	int count;                      //�������J�E���g����
	int jump;                       //�W�����v�̒l
	int jump_power;                 //�W�����v�̗�
    float player_x, player_y;       //�v���C���[�̍��W
	Player* player;                 //�����œn���p�ϐ�
	

	BULLET** bullet;             //�e�̔z��

public:
	Player();
	~Player();
	void Draw()const;
	void Update();

	void Shoot_Gun();

	float GetLocationX() { return location.x; }
	float GetLocationY() { return location.y; }

};

