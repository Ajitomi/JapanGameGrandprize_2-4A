#include "ItemController.h"
#include "EnemyBase.h"
#include "Player.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
ItemController::ItemController()
{
	item_volume = 0;
	item = nullptr;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
ItemController::~ItemController()
{
	for (int i = 0; i < item_volume; i++)
	{
		delete item[i];
	}

	delete[] item;
}

//-----------------------------------
//�X�V
//-----------------------------------
void ItemController::Update(class Player* player)
{
	for (int i = 0; i < item_volume; i++)
	{
		if (item[i] == nullptr)
		{
			break;
		}

		item[i]->Update(player);

		if (item[i]->HitBox(player))
		{
			player->SetElementItem(item[i]);
			delete item[i];
			item[i] = nullptr;
			SortItem(i);
		}
	}
}

//-----------------------------------
//�A�C�e���̐���
//-----------------------------------
void ItemController::SpawnItem(class EnemyBase* enemy_base)
{

	int old_item_volume = item_volume;//�����\�ȃG�l�~�[��

	item_volume += enemy_base->GetDropVolume();
	ArrangementItem(old_item_volume);

	int volume = 0; //������
	int j = old_item_volume;

	//�A�C�e���̐���
	for (int i = 0; i < enemy_base->GetDropTypeVolume(); i++)
	{
		volume = enemy_base->GetDropItem(i).GetVolume();

		while (0 < volume)
		{
			item[j++] = new Item(enemy_base->GetDropItem(i).GetType(), enemy_base->GetLocation());
			volume--;
		}
	}
}

//-----------------------------------
//�A�C�e���̕��ёւ�
//-----------------------------------
void ItemController::SortItem(int item_num)
{
	int old_item_volume = item_volume;//�����\�ȃA�C�e����

	//�e�̒��g���\�[�g����
	for (int i = item_num + 1; i < item_volume; i++)
	{
		if ((item[i] == nullptr))
		{
			break;
		}

		item[i - 1] = item[i];
		item[i] = nullptr;
		item_volume--;
	}

	ArrangementItem(old_item_volume);
}

//-----------------------------------
//�A�C�e���̐���
//-----------------------------------
void ItemController::ArrangementItem(int old_item_volume)
{
	Item** temporary_item; //���p

	//���Ƃ��Ƃ̃A�C�e���ꎞ�I�ɔ���
	temporary_item = item;

	item = new Item * [item_volume];

	//�������A�C�e�������ɖ߂�
	if (old_item_volume < item_volume)
	{
		for (int i = 0; i < old_item_volume; i++)
		{
			if (temporary_item == nullptr)
			{
				break;
			}
			item[i] = temporary_item[i];
		}
	}
	else
	{
		for (int i = 0; i < item_volume; i++)
		{
			item[i] = temporary_item[i];
		}
	}
	
	delete[] temporary_item;
}

//-----------------------------------
//�`��
//-----------------------------------
void ItemController::Draw() const
{
	for (int i = 0; i < item_volume; i++)
	{
		if (item[i] == nullptr)
		{
			break;
		}

		item[i]->Draw();
	}
}