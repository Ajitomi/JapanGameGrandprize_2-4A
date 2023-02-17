#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "Bullet.h"
#include "Stage/Stage.h"

#define JUMP_INERTIA 0.2
#define WARK_INERTIA 0.5
#define HP_MAX 100

enum class PlayerState
{
	stop = 0,
	move_left,
	move_right,
	jump,
	down,
	death
};



class Player : public BoxCollider
{
private:
	int image;						//�摜�p�ϐ�
	int image_size_x, image_size_y; //�摜�̃T�C�Y
	int hp;							//�̗�
	int bullet_count;				//�������e�̐�
	int count;                      //�������J�E���g����
	int not_jet_count;              //����łȂ����𐔂���
	float gravity_down;				//���~���̒l
	float fuel;						//�R��
	float jump;                     //�W�����v�̒l
	float jump_power;               //�W�����v�̗�
	float speed_x;
	int select_count;
	int i;                          //�X�C�b�`���ł̃��[�v�p

	Player* player;

	Attribute attribute[6];         //�e�̑���
	int attribute_c[6];
	int display_attribute; //��ʂɕ\�������鑮��

	PlayerState player_state;
	
	
	Bullet** bullet;             //�e�̔z��
	Stage* stage;                //�X�e�[�W�ւ̃|�C���^
	EfectBeam* beam;

public:
	Player();
	Player(Stage*);
	~Player();
	void Draw()const;
	void Update();
	void Element_Update();

	void RightMove();
	void LeftMove();
	void NotInputStick();
	void Jump();
	void NotJump();
	void Shoot_Gun();
	void SortBullet(int);
	void Hp_Damage(int);
	void Hp_Heal(int);

	Bullet* GetBullet(int i) { return bullet[i]; }
	PlayerState GetState() { return player_state; }

	POINT collision_dir;

};
