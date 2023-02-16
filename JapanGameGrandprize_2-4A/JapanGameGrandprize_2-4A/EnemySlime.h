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
	BOUNCE, //�ǁA�G�ɒ��˕Ԃ�
	DEATH,  //���S
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	int direction;

	int slime_image;

	Location jump_distance;

	ElementItem drop_item;

	SLIME_STATE state;

public:
	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update()override;
	//�`��
	virtual void Draw()const override;

	void HitPlayer(BoxCollider* boxcollider);
	void HitStage();
	void AttackJudgement(BoxCollider* boxcollider);
	void Attack();

	virtual void HitBullet(Bullet* bullet)override {};
};
