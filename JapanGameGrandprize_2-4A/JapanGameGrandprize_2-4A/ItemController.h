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

	//�X�V
	void Update(class Player* player);

	//�`��
	void Draw() const;

	//�A�C�e���̐���
	void SpawnItem(class EnemyBase* enemy);

	//�A�C�e���̕��ёւ�
	void SortItem(int item_num);

	//�A�C�e���̐���
	void ArrangementItem(int old_item_volume);
};