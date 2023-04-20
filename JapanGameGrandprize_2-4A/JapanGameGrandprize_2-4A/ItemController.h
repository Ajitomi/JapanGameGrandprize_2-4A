#pragma once
#include"Item.h"
#include "ElementItem.h"
#include <vector>

class ItemController
{
private:

	int item_volume; //�������Ă���A�C�e���̗�
	int item_max; //�A�C�e���̐����ł���ő吔
	Item** item; //�A�C�e��
public:

	//�R���X�g���N�^
	ItemController();

	//�f�X�g���N�^
	~ItemController();

	//�X�V
	void Update( class Player* player);

	//�`��
	void Draw() const;

	//�A�C�e���̐���
	void SpawnItem(const class EnemyBase* enemy);

	void Stage_SpawnItem(int drop_volume, int dorp_type_volume, Location location, std::vector<ElementItem>element_item);

	//�A�C�e���̕��ёւ�
	void SortItem(const int item_num);

	//�A�C�e���̐���
	void ArrangementItem(const int old_item_volume);

	Item** GetItem() { return item; }
};