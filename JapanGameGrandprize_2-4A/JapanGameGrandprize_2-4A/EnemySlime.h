#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"

class EnemySlime : public EnemyBase , public BoxCollider
{
private:
	int slime_x;
	int slime_y;

	int draw_x;
	int draw_y;

	int a;
public:
	EnemySlime();
	~EnemySlime() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update()override;
	//�`��
	virtual void Draw()const override;

	//void SetSlimeX(int a);
	//int SetSlimeX();*/

	void Hit();
};
