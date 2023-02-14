#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"


struct ATTACK_START
{
	float x;	//�c
	float y;	//��
};

enum DIRECTION
{
	left = -1,
	right = 1
};

enum class SLIME_STATE
{
	IDOL,   //�A�C�h�����
	MOVE,   //�ړ�
	ATTACK, //�U��
	DEATH,  //���S
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	int a;
	int direction;
	int jump_angle;

	ATTACK_START attack_start;
	SLIME_STATE state;

public:
	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update()override;
	//�`��
	virtual void Draw()const override;

	void Hit();
	void HitStage();
	void AttackJudgement(BoxCollider* boxcollider);
	void Attack();
};
