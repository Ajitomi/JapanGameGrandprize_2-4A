#pragma once
#include"EnemyBase.h"

class EnemySlime : public EnemyBase
{
private:
	int slime_x;
	int slime_y;

public:
	EnemySlime();
	~EnemySlime() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update()override;
	//�`��
	virtual void Draw()const override;

	/*void SetSlimeX(int a);
	int SetSlimeX();*/
};