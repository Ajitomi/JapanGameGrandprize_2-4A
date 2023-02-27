#pragma once
#include "SphereCollider.h"
#include "EnumElementItem.h"
#include "Player.h"

class Item :
	public SphereCollider
{
private:

	int color; //�F
	int speed; //���x
	ELEMENT_ITEM element_type; //���f
public:

	//�R���X�g���N�^
	Item();
	Item(ELEMENT_ITEM type, Location location);

	//�X�V
	void Update(Player* player);

	//�`��
	void Draw()const;

	//���f�̃^�C�v�̎擾
	ELEMENT_ITEM GetElementType() const;
};