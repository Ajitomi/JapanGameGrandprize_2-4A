#include "Wyvern.h"
#include "Player.h"
#include "BulletManager.h"

//�ړ��X�s�[�h
#define WYVERN_MOVE_SPEED 2
//���P�U���X�s�[�h
#define WYVERN_ASSAULT_SPEED 5

#define WYVERN_MIN_DROP 1
#define WYVERN_DROP 8

#define BLESS_INTERVAL 300
#define TRIPLE_BLESS_INTERVAL 600
#define ASSAULT_INTERVAL 480

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Wyvern::Wyvern(Location spawn_location)
{
	/*������*/
	can_delete = false;
	left_move = true;
	attack_end = false;
	attack = false;

	hp = 100;
	damage = 0;

	bless_interval = BLESS_INTERVAL;
	triple_bless_interval = TRIPLE_BLESS_INTERVAL;
	assault_interval = ASSAULT_INTERVAL;

	shot_rate = 0;
	assault_speed[0] = 0;
	assault_speed[1] = 0;
	image_argument = 0;
	speed = 0;
	kind = ENEMY_KIND::WYVERN;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::FIRE;
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	location = spawn_location;
	/*�����蔻��̐ݒ�*/
	area.width = 40;
	area.height = 80;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [FIRE_DROP];
	drop_type_volume = FIRE_DROP;

	int volume = 0;

	for (int i = 0; i < FIRE_DROP; i++)
	{
		volume = WYVERN_MIN_DROP + GetRand(WYVERN_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	images = nullptr;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Wyvern::~Wyvern()
{
	delete[] images;
}

//-----------------------------------
//�X�V
//-----------------------------------
void Wyvern::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//�O�̍��W

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		if (bless_interval < 0) //�u���X�Ɉڍs
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::BLESS;
			break;
		}

		if (triple_bless_interval < 0) //�g���v���u���X�Ɉڍs
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::TRIPLE_BRACE;
			break;
		}

		if (assault_interval < 0) //�A�T���g�Ɉڍs
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::ASSAULT;
			break;
		}
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
	Poison();
	Paralysis();

	if ((state != ENEMY_STATE::DEATH) && (state != ENEMY_STATE::IDOL))
	{

	}
	if (CheckHp() && (state != ENEMY_STATE::DEATH))
	{
		state = ENEMY_STATE::DEATH;
	}
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Wyvern::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -WYVERN_MOVE_SPEED;
		}
		else
		{
			speed = WYVERN_MOVE_SPEED;
		}
	}
}

//-----------------------------------
//�ړ�
//-----------------------------------
void Wyvern::Move(const Location player_location)
{
	if (ScreenOut())
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//�ړ����̃A�j���[�V����
//-----------------------------------
void Wyvern::MoveAnimation()
{

}

//-----------------------------------
//����
//-----------------------------------
void Wyvern::Fall()
{

}

//-----------------------------------
//�U��
//-----------------------------------
void Wyvern::Attack(const Location)
{
	switch (attack_state)
	{
	case WYVERN_ATTACK::BLESS:
		break;
	case WYVERN_ATTACK::TRIPLE_BRACE:
		break;
	case WYVERN_ATTACK::ASSAULT:
		break;
	case WYVERN_ATTACK::NONE:
		break;
	default:
		break;
	}

	if(attack_end)
	{
		state = ENEMY_STATE::MOVE;
		switch (attack_state) //�C���^�[�o���̐ݒ�
		{
		case WYVERN_ATTACK::BLESS:
			bless_interval = BLESS_INTERVAL;
			break;
		case WYVERN_ATTACK::TRIPLE_BRACE:
			triple_bless_interval = TRIPLE_BLESS_INTERVAL;
			break;
		case WYVERN_ATTACK::ASSAULT:
			assault_interval = ASSAULT_INTERVAL;
			break;
		case WYVERN_ATTACK::NONE:
			break;
		default:
			break;
		}
		attack_state = WYVERN_ATTACK::NONE;
		attack_end = false;
	}
}

//-----------------------------------
//�u���X�̐���
//-----------------------------------
void Wyvern::CreateBless(const Location)
{

}

//-----------------------------------
//���P�U��
//-----------------------------------
void Wyvern::Assault(const Location)
{

}

//-----------------------------------
// �U�����Ă��Ȃ�
//-----------------------------------
void Wyvern::AttackNone()
{

}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Wyvern::Hit()
{

}

//-----------------------------------
//���S
//-----------------------------------
void Wyvern::Death()
{

}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Wyvern::HitBullet(const BulletBase* bullet)
{

}

//-----------------------------------
//�`��
//-----------------------------------
void Wyvern::Draw() const
{

}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Wyvern::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//�X�V(DotByDot)
//-----------------------------------
void Wyvern::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void Wyvern::DebugDraw()
{

}
#endif //_DEBUG