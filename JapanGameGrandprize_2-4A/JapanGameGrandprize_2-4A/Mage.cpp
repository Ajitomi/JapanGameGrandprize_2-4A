#include "Mage.h"
#include "CameraWork.h"
#include "MageBullet.h"
#include "BulletManager.h"

//���@�e�̔��˃��[�g
#define MAGE_SHOT_RATE 20

//�ړ����x
#define MAGE_SPEED 2

//�h���b�v��
#define MAGE_MIN_DROP 0
#define MAGE_MAX_DROP 6

#define MAGE_SHOT_RATE 20

//�̗�
#define MAGE_HP 100

//�ړ��͈�
#define MAGE_TELEPORT_AREA 200

//�U���Ԋu
#define MAGE_ATTACK_INTERVAL 120

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Mage::Mage() 
{
	/*������*/
	can_delete = false;
	left_move = true;
	hp = MAGE_HP;
	shot_rate = 0;
	shot_count = 0;
	attack_interval = 0;
	speed = MAGE_SPEED;
	kind = ENEMY_KIND::MAGE;
	type = new ENEMY_TYPE;
	
	*type = static_cast<ENEMY_TYPE>(1 + GetRand(3));
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;

	/*�����蔻��̐ݒ�*/
	location.x = 660.0f;
	location.y = 1120.0f;
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
		image = 0xff0000;
		break;
	case ENEMY_TYPE::WATER:
		drop = WATER_DROP;
		image = 0x0000ff;
		break;
	case ENEMY_TYPE::WIND:
		drop = WIND_DROP;
		image = 0xffffff;
		break;
	case ENEMY_TYPE::SOIL:
		drop = SOIL_DROP;
		image = 0xffff00;
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
}

//-----------------------------------
//�X�V
//-----------------------------------
void Mage::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//�O�̍��W

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());
		break;
	case ENEMY_STATE::FALL:
		Fall();
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}

	if (0 <= attack_interval)
	{
		attack_interval--;
	}

	Poison();
	Paralysis();

	if (CheckHp() && (state != ENEMY_STATE::DEATH))
	{
		state = ENEMY_STATE::DEATH;
	}
}


//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Mage::Idol()
{
	Location scroll; //��ʃX�N���[�����l������X���W
	Location camera = CameraWork::GetCamera(); //�J����
	scroll = location - camera;

	if ((-area.width < scroll.x) && (scroll.x < SCREEN_WIDTH + area.width) &&
		(-area.height < scroll.y) && (scroll.y < SCREEN_HEIGHT + area.height))
	{
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//�ړ�
//-----------------------------------
void Mage::Move(const Location player_location)
{
	Location scroll; //��ʃX�N���[�����l������X���W

	if (attack_interval < 0)
	{
		state = ENEMY_STATE::ATTACK;
	}

	scroll.x = location.x - CameraWork::GetCamera().x;
	scroll.y = location.y - CameraWork::GetCamera().y;

	if ((scroll.x < -area.width) || (SCREEN_WIDTH + area.width < scroll.x) ||
		(scroll.y < -area.height) || (SCREEN_HEIGHT + area.height < scroll.y))
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//�e���|�[�g
//-----------------------------------
void Mage::Teleport()
{

}

//-----------------------------------
//����
//-----------------------------------
void Mage::Fall()
{

}

//-----------------------------------
//�U��
//-----------------------------------
void  Mage::Attack(Location player_location)
{
	CreateBullet(player_location);
	
	if (shot_count >= MAGE_BULLET_MAX)
	{
		state = ENEMY_STATE::MOVE;
		shot_count = 0;
		attack_interval = MAGE_ATTACK_INTERVAL;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Mage::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Mage::Death()
{
	can_delete = true;
}

//-----------------------------------
//�e�̐���
//-----------------------------------
void Mage::CreateBullet(Location player_location)
{
	shot_rate++;

	if (shot_rate % MAGE_SHOT_RATE == 0)
	{
		BulletManager::GetInstance()->CreateEnemyBullet
		(new MageBullet(*type, location, player_location));

		shot_count++;
	}
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Mage::HitBullet(const BulletBase* bullet)
{
	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
		break;
	case ATTRIBUTE::EXPLOSION:
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
		break;
	case ATTRIBUTE::MELT:
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
		break;
	case ATTRIBUTE::POISON:
		poison_damage = bullet->GetDamage();
		poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
		break;
	case ATTRIBUTE::PARALYSIS:
		paralysis_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}
}

//-----------------------------------
//�`��
//-----------------------------------
void Mage::Draw() const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2, image, TRUE);
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Mage::GetLocation() const
{
	return location;
}