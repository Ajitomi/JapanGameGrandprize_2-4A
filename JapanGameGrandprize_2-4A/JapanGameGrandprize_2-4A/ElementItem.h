#pragma once

//���f�\����
enum class  ELEMENT_ITEM
{
	OXYGEN,      //�_�f
	HYDROGEN,	 //���f
	NITROGEN,	 //���f
	CARBON,		 //�Y�f
	SULFUR,		 //����
	CHLORINE,	 //���f
	URANIUM,	 //�E����
	NONE
};

class ElementItem
{
private:
	unsigned int volume; //��
	ELEMENT_ITEM type; //���f�^�C�v
public:
	//�R���X�g���N�^
	ElementItem();
	ElementItem(ELEMENT_ITEM type);

	//���f�̗ʂ��擾
	unsigned int GetVolume()const;

	//���f�^�C�v�̎擾
	ELEMENT_ITEM GetType() const;
};

