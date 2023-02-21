#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"
class BulletBase
{
protected:
	float damage;          //�e�̃_���[�W
	float debuff_time;	 //�e�̌��ʎ���
	int efect_count;	 //�G�t�F�N�g�̎���
	float scrool_x;      //�e�̃X�N���[���̒l
	bool delete_flg;     //�e�̍폜�t���O
	bool efect_end;		 //�G�t�F�N�g�̏I���t���O


	ATTRIBUTE attribute;
	EfectExplosion* efect_explosion;
public:
	BulletBase();
	BulletBase(float,float);
	~BulletBase() {};

	virtual void Draw() const = 0;
	virtual void Update() = 0;

	bool GetEfectFlg();
	float GetDebuffTime();
	float GetDamage();
	ATTRIBUTE GetAttribute();

};