#include "ItemController.h"
#include "EnemyBase.h"
#include "Player.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
ItemController::ItemController()
{
	item_volume = 0;
	item_max = 0;
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
void ItemController::Update(Player* player)
{
	for (int i = 0; i < item_volume; i++)
	{
		if (item[i] == nullptr)
		{
			break;
		}

		item[i]->Update(player->GetLocation());

		if (item[i]->HitBox(player))
		{
			player->SetElementItem(item[i]);
			delete item[i];
			item[i] = nullptr;
			SortItem(i);
			i--;
			item_volume--;
		}
	}
}

//-----------------------------------
//�A�C�e���̐���
//-----------------------------------
void ItemController::SpawnItem(const EnemyBase* enemy_base)
{

	int old_item_max = item_max;//�����\�ȃG�l�~�[��

	item_volume += enemy_base->GetDropVolume();

	if (item_max < item_volume)
	{
		item_max = item_volume;
		ArrangementItem(old_item_max);
	}

	int volume = 0; //������
	int j = 0;

	//�A�C�e���̐���
	for (int i = 0; i < enemy_base->GetDropTypeVolume(); i++)
	{
		volume = enemy_base->GetDropItem(i).GetVolume();

		for (int j = 0; j < volume; j++)
		{
			for (int n = 0; n < item_max; n++)
			{
				if (item[n] == nullptr)
				{
					item[n] = new Item(enemy_base->GetDropItem(i).GetType(),
						                enemy_base->GetLocation());
					break;
				}
			}
		}
	}
}

//-----------------------------------
//�A�C�e���̕��ёւ�
//-----------------------------------
void ItemController::SortItem(const int item_num)
{
	//�e�̒��g���\�[�g����
	for (int i = item_num + 1; i < item_max; i++)
	{
		if ((item[i] == nullptr))
		{
			break;
		}

		item[i - 1] = item[i];
		item[i] = nullptr;
	}
}

//-----------------------------------
//�A�C�e���̐���
//-----------------------------------
void ItemController::ArrangementItem(const int old_item_max)
{
	if (item == nullptr)
	{
		//�A�C�e���̏�����
		item = new Item * [item_max];

		for (int i = 0; i < item_max; i++)
		{
			item[i] = nullptr;
		}
	}
	else
	{
		Item** temporary_item; //���p

		//���Ƃ��Ƃ̃A�C�e���ꎞ�I�ɔ���
		temporary_item = item;

		item = new Item * [item_max];

		//�������A�C�e�������ɖ߂�
		item = temporary_item;

		for (int i = old_item_max; i < item_max; i++)
		{
			item[i] = nullptr;
		}

	}

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