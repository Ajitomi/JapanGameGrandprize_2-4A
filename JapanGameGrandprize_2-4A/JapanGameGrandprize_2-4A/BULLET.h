#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"
#include "Stage/Stage.h"
#include "Stage/MapChip.h"

#define BULLET_SPEED 20
#define EXPLOSION_BULLET_SPEED 10
#define MELT_BULLET_SPEED 15
#define PARARYSIS_BULLET_SPEED 10
#define POISON_BULLET_SPEED 18

#define ORANGE 0xff8f00
#define PURPLE 0x00ff00
#define BLUE 0x0000ff
#define GLAY 0xbebebe

enum class PLAYER_STATE;

class BulletBase : public SphereCollider
{
protected:

	Area area;           //�͈�
	float damage;        //�e�̃_���[�W
	float damage_second; //�b�ԃ_���[�W
	int debuff_time;	 //�e�̌��ʎ���
	int efect_count;	 //�G�t�F�N�g�̎���
	float scrool_x;      //�e�̃X�N���[���̒l(X)
	float scrool_y;		 //�e�̃X�N���[���̒l(Y)
	bool delete_flg;     //�e�̍폜�t���O
	bool efect_end;		 //�G�t�F�N�g�̏I���t���O
	bool player_direction;//�v���C���[�̌���
	ChemicalFormulaParameter* chemical_formula;//������

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
	int GetDebuffTime() const;
	int GetDamage() const;
	ATTRIBUTE GetAttribute() const;
};