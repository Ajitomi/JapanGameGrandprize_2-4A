#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"

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

	Location attack_start;
	Location attack_speed;

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

	virtual void HitBullet(Bullet* bullet)override {};
};
