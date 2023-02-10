#pragma once
#include "EfectExplosion.h"
#include "EfectBeam.h"

enum class BULLET_TYPE
{
	NORMAL = 0,  //�m�[�}���e
	EXPLOSION,   //����
	MELT,        //�n����i�_�j
	WARTER,      //��
	POISON,      //�Łi�p���_���j
	PARALYSIS,   //��Ⴡi�ړ����x�ቺ�j
	FROZEN,      //�X�i��莞�ԍd���j
	SPECIAL      //�K�E�Z�i�E�������g�p���ăr�[���j
};



class BULLET
{
private:
	float bullet_x, bullet_y;
	bool delete_flg;
	BULLET_TYPE type;

	EfectExplosion* efect_explosion;
	EfectBeam* efect_beam;

public:
	BULLET();
	BULLET(float,float,BULLET_TYPE);
	~BULLET() {};

	void Draw()const;
	void Update();

	bool GetDeleteFlg() { return delete_flg; }
};