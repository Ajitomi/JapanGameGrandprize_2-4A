#pragma once
#include"Item.h"

class ItemController
{
private:
	int item_volume; //�������Ă���A�C�e���̗�

	Item** item; //�A�C�e��
public:

	//�R���X�g���N�^
	ItemController();

	//�f�X�g���N�^
	~ItemController();
	//�A�C�e���̐���
	void SpawnItem();

	//�A�C�e���̕��ёւ�
	void SortItem();
};