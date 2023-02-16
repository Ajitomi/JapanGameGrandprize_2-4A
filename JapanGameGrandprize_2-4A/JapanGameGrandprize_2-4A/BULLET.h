#pragma once
#include "EfectExplosion.h"
class Bullet
{
protected:
	int damage;          //�e�̃_���[�W
	int efect_count;	 //�G�t�F�N�g�̎���
	bool delete_flg;     //�e�̍폜�t���O
	bool efect_end;		 //�G�t�F�N�g�̏I���t���O

	EfectExplosion* efect_explosion;
public:
	Bullet();
	Bullet(float,float);
	~Bullet() {};

	virtual void Draw() const = 0;
	virtual void Update() = 0;


	bool GetEfectFlg();
};