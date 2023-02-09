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
	int not_jet_count;              //����łȂ����𐔂���
	float fuel;						//�R��
	float jump;                       //�W�����v�̒l
	float jump_power;                 //�W�����v�̗�
	

	BULLET** bullet;             //�e�̔z��

public:
	Player();
	~Player();
	void Draw()const;
	void Update();

	void Shoot_Gun();
	void SortBullet(int);

	float GetLocationX() { return location.x; }
	float GetLocationY() { return location.y; }

};
