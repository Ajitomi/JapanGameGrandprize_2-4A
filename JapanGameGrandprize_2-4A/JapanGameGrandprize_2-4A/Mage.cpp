#include "Mage.h"

//���@�e�̔��˃��[�g
#define MAGE_SHOT_RATE 20

//�ړ����x
#define MAGE_SPEED 2

//�h���b�v��
#define MAGE_MIN_DROP 0
#define MAGE_MAX_DROP 6

#define MAGE_SHOT_RATE 20

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Mage::Mage() 
{
	/*������*/
	can_delete = false;
	hp = 0;
	shot_rate = 0;
	speed = MAGE_SPEED;
	kind = ENEMY_KIND::MAGE;
	type = new ENEMY_TYPE;
	
	*type = static_cast<ENEMY_TYPE>(1 + GetRand(3));
	state = MAGE_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;

	/*�����蔻��̐ݒ�*/
	location.x = 640.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//�h���b�v�A�C�e���̐ݒ�
	drop = 0;

	switch (*type)
	{
	case ENEMY_TYPE::NORMAL:
		break;
	case ENEMY_TYPE::FIRE:
		drop = FIRE_DROP;
		break;
	case ENEMY_TYPE::WATER:
		drop = WATER_DROP;
		break;
	case ENEMY_TYPE::WIND:
		drop = WIND_DROP;
		break;
	case ENEMY_TYPE::SOIL:
		drop = SOIL_DROP;
		break;
	case ENEMY_TYPE::THUNDER:
		break;
	default:
		break;
	}

	drop_element = new ElementItem * [drop];
	drop_type_volume = drop;

	int volume = 0;

	for (int i = 0; i < drop; i++)
	{

		volume = MAGE_MIN_DROP + GetRand(MAGE_MAX_DROP);

		switch (*type)
		{
		case ENEMY_TYPE::NORMAL:
			break;
		case ENEMY_TYPE::FIRE:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(1 + i));
			break;
		case ENEMY_TYPE::WATER:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			}
			break;
		case ENEMY_TYPE::WIND:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(1 + i));
			}
			break;
		case ENEMY_TYPE::SOIL:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			break;
		case ENEMY_TYPE::THUNDER:
			break;
		default:
			break;
		}

		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	//�e�̏�����
	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		bullet[i] = nullptr;
	}

	this->player = player;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Mage::~Mage()
{
	delete type;

	for (int i = 0; i < drop; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		delete bullet[i];
	}
}

//-----------------------------------
//�X�V
//-----------------------------------
void Mage::Update()
{
	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		if (bullet[i] == nullptr)
		{
			break;
		}

		bullet[i]->Update();
	}
}


//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Mage::Idol()
{

}

//-----------------------------------
//�ړ�
//-----------------------------------
void Mage::Move(const Location player_location)
{

}

//-----------------------------------
//�U��
//-----------------------------------
AttackResource Mage::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Mage::Death()
{

}

//-----------------------------------
//�e�̐���
//-----------------------------------
void Mage::CreateBullet()
{
	shot_rate++;

	if (shot_rate % MAGE_SHOT_RATE == 0)
	{
		for (int i = 0; i < MAGE_BULLET_MAX; i++)
		{
			if (bullet[i] == nullptr)
			{
				bullet[i] = new MageBullet(*type, location, player->GetLocation());
				break;
			}
		}
	}
}

//-----------------------------------
//�e�̕��ёւ�
//-----------------------------------
void Mage::SortBullet(int bullet_num)
{
	//�e�̒��g���\�[�g����
	for (int i = bullet_num + 1; i < MAGE_BULLET_MAX; i++)
	{
		if ((bullet[i] == nullptr))
		{
			break;
		}
		bullet[i - 1] = bullet[i];
		bullet[i] = nullptr;
	}
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
bool Mage::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //�߂�l

	return ret;
}

//-----------------------------------
//�`��
//-----------------------------------
void Mage::Draw() const
{

}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Mage::GetLocation() const
{
	return location;
}