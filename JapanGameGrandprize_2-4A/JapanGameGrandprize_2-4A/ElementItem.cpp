#include "ElementItem.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
ElementItem::ElementItem()
{

	volume = 0;
	type = ELEMENT_ITEM::NONE;
}

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
ElementItem::ElementItem(ELEMENT_ITEM type)
{

	volume = 0;
	this->type = type;
}

//-----------------------------------
//���f�̗ʂ��擾
//-----------------------------------
unsigned int ElementItem::GetVolume()const
{

	return volume;
}

//-----------------------------------
//���f�^�C�v�̎擾
//-----------------------------------
ELEMENT_ITEM ElementItem::GetType() const
{

	return type; 
}

//-----------------------------------
//���f�̗ʂ�ݒ�
//-----------------------------------
void ElementItem::SetVolume(unsigned int num)
{

	volume = num;
}