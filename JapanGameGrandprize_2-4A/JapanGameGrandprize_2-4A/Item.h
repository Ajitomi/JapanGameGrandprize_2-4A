#pragma once
#include"SphereCollider.h"

class Item :
	public SphereCollider
{
private:
	int color; //�F
public:
	//�R���X�g���N�^
	Item();

	//�X�V
	void Update();

	//�`��
	void Draw()const;
};

