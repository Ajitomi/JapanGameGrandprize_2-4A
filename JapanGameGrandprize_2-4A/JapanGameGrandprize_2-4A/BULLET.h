#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"

enum class PLAYER_STATE;
class BulletBase : public SphereCollider
{
protected:
	float damage;          //�e�̃_���[�W
	int debuff_time;	 //�e�̌��ʎ���
	int efect_count;	 //�G�t�F�N�g�̎���
	float scrool_x;      //�e�̃X�N���[���̒l
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
	virtual void Update() = 0;

	bool GetEfectFlg() const;
	float GetDebuffTime() const;
	float GetDamage() const;
	ATTRIBUTE GetAttribute() const;

};