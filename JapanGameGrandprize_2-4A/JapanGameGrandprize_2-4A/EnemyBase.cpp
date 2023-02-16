#include "DxLib.h"
#include "EnemyBase.h"


//-----------------------------------
// HP��0���ǂ������f(0�ɂȂ�����true)
//-----------------------------------
bool EnemyBase::CheckHp()
{
	bool ret = false;
	if (hp <= 0)
	{
		ret = true;
	}
	return ret;
}

//-----------------------------------
//�A�C�e���̐���
//-----------------------------------
void EnemyBase::CreateDropItem(int drop_num,Location location)
{
	int volume = 0; //������
	int j = 0;
	for (int i = 0; i < drop_num; i++)
	{
		volume = drop_element[i]->GetVolume();
		while (0 < volume)
		{
			drop_item[j++] = new Item(drop_element[i]->GetType(), location);
			volume--;
		}
	}
}

//-----------------------------------
//�A�C�e���̕��ёւ�
//-----------------------------------
void EnemyBase::SortDropitem(int item_num)
{
	//�e�̒��g���\�[�g����
	for (int i = item_num + 1; i < drop_volume; i++)
	{
		if ((drop_item[i] == nullptr))
		{
			break;
		}
		drop_item[i - 1] = drop_item[i];
		drop_item[i] = nullptr;
	}
}
//-----------------------------------
// �h���b�v�A�C�e���̎擾
//-----------------------------------
ElementItem EnemyBase::GetDropItem(int i) const
{ 
	return *drop_element[i]; 
}

//-----------------------------------
// �G�l�~�[�̎�ނ̎擾
//-----------------------------------
ENEMY_KIND EnemyBase::GetEnemyKind() const
{
	return kind;
}

