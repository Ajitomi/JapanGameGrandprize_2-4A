#include "ItemController.h"
#include "EnemyBase.h"
#include "Player.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
ItemController::ItemController()
{
	item_volume = 0;
	item = nullptr;
}

//-----------------------------------
//デストラクタ
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
//更新
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
//アイテムの生成
//-----------------------------------
void ItemController::SpawnItem(class EnemyBase* enemy_base,Location spawn_location)
{
	EnemyBase* enemy = enemy_base;

	int old_item_volume = item_volume;//生成可能なエネミー数

	item_volume += enemy_base->GetDropVolume();
	ArrangementItem(old_item_volume);

	int volume = 0; //生成数
	int j = old_item_volume;

	//アイテムの生成
	for (int i = 0; i < enemy->GetDropTypeVolume(); i++)
	{
		volume =enemy->GetDropItem(i).GetVolume();
		while (0 < volume)
		{
			item[j++] = new Item(enemy->GetDropItem(i).GetType(), spawn_location);
			volume--;
		}
	}
}

//-----------------------------------
//アイテムの並び替え
//-----------------------------------
void ItemController::SortItem(int item_num)
{
	int old_item_volume = item_volume;//生成可能なアイテム数

	//弾の中身をソートする
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
//アイテムの整理
//-----------------------------------
void ItemController::ArrangementItem(int old_item_volume)
{
	Item** temporary_item; //避難用

	//もともとのアイテム一時的に避難する
	temporary_item = item;

	item = new Item * [item_volume];

	//避難させたアイテムを元に戻す
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
//描画
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

