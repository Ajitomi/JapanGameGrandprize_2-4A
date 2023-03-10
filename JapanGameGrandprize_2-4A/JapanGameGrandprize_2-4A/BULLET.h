#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"
#include "Stage/Stage.h"
#include "Stage/MapChip.h"

enum class PLAYER_STATE;

class BulletBase : public SphereCollider
{
protected:

	Area area;           //�͈�
	float damage;        //�e�̃_���[�W
	int debuff_time;	 //�e�̌��ʎ���
	int efect_count;	 //�G�t�F�N�g�̎���
	float scrool_x;      //�e�̃X�N���[���̒l(X)
	float scrool_y;		 //�e�̃X�N���[���̒l(Y)
	bool delete_flg;     //�e�̍폜�t���O
	bool efect_end;		 //�G�t�F�N�g�̏I���t���O
	bool player_direction;//�v���C���[�̌���

	PLAYER_STATE player_state;
	ATTRIBUTE attribute;
	EfectExplosion* efect_explosion;
public:

	BulletBase();
	BulletBase(float,float);
	~BulletBase() {};

	virtual void Draw() const = 0;
	virtual void Update(const Stage*) = 0;

	bool HitBlock(const Stage*);
	bool GetEfectFlg() const;
	float GetDebuffTime() const;
	float GetDamage() const;
	ATTRIBUTE GetAttribute() const;
};