#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "BULLET.h"
#include "Stage/Stage.h"



class Player : public BoxCollider
{
private:
	int image;						//�摜�p�ϐ�
	int image_size_x, image_size_y; //�摜�̃T�C�Y
	int bullet_count;				//�������e�̐�
	int count;                      //�������J�E���g����
	int not_jet_count;              //����łȂ����𐔂���
	float gravity_down;				//���~���̒l
	float fuel;						//�R��
	float jump;                     //�W�����v�̒l
	float jump_power;               //�W�����v�̗�
	float speed_x;
	int select_count;

	Attribute attribute[6];         //�e�̑���
	int attribute_c[6];
	int display_attribute; //��ʂɕ\�������鑮��
	
	Bullet** bullet;             //�e�̔z��
	Stage* stage;
	EfectBeam* beam;

public:
	Player();
	~Player();
	void Draw()const;
	void Update();
	void Element_Update();

	void Shoot_Gun();
	void SortBullet(int);

	Bullet* GetBullet(int i) { return bullet[i]; }

};
