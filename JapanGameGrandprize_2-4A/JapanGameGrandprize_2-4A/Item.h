#pragma once
#include "SphereCollider.h"
#include "EnumElementItem.h"
class Item :
	public SphereCollider
{
private:
	int color; //�F
public:
	//�R���X�g���N�^
	Item();
	Item(ELEMENT_ITEM type, Location location);

	//�X�V
	void Update();

	//�`��
	void Draw()const;
};

