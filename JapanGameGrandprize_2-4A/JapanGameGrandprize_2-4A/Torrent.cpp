#include "Torrent.h"
#include "DxLib.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "TorrentBullet.h"
#include "BulletManager.h"

//�ړ����x
#define TORRENT_SPEED 4

//�^�b�N���̃_���[�W
#define TORRENT_TACKLE_DAMAGE 10

//���ˑ��x
#define TORRENT_SHOT_RATE 30

//�h���b�v��
#define TORRENT_MIN_DROP 20
#define TORRENT_DROP 20

//�t���ς��΂��Ă��鎞��
#define LEAF_CUTTER_TIME 1800

//���̗t���ς��΂��U���Ɉڂ鎞��
#define LEAF_CUTTER_INTERVAL 1800

//�؂̎��𗎂Ƃ��Ă��鎞��
#define DROP_NUTS_TIME 1200

//���̖؂̎��𗎂Ƃ��U���Ɉڂ鎞��
#define DROP_NUTS_INTERVAL 1200


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Torrent::Torrent()
{
	left_move = false;
	attack = false;
	shot_rate = 0;
	leaf_cutter_interval = 0;
	drop_nuts_interval = 0;
	animation = 0;
	image_argument = 0;
	attack_time = 0;
	attack_state = TORRENT_ATTACK::NONE;


	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < SOIL_DROP; i++)
	{
		volume = TORRENT_MIN_DROP + GetRand(TORRENT_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Torrent::~Torrent()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete type;
}

//-----------------------------------
//�X�V
//-----------------------------------
void Torrent::Update(const Player* player, const Stage* stage)
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
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Torrent::Idol()
{
}

//-----------------------------------
//�ړ�
//-----------------------------------
void Torrent::Move(const Location player_location)
{
}

//-----------------------------------
//����
//-----------------------------------
void Torrent::Fall()
{
}

//-----------------------------------
//�U��
//-----------------------------------
void  Torrent::Attack(Location player_location)
{

	if (0 < leaf_cutter_interval) //���̗t���ς��΂��U���܂ł̎��Ԃ̃J�E���g
	{
		leaf_cutter_interval--;
	}

	if (0 < drop_nuts_interval) //���̖؂̎��𗎂Ƃ��U���܂ł̎��Ԃ̃J�E���g
	{
		drop_nuts_interval--;
	}

	switch (attack_state)
	{
	case TORRENT_ATTACK::TACKLE:
		Tackle();
		break;
	case TORRENT_ATTACK::LEAF_CUTTER:
		LeafCutter(player_location);
		break;
	case TORRENT_ATTACK::DROP_NUTS:
		DropNuts();
		break;
	case TORRENT_ATTACK::NONE:
		AttackNone();
		break;
	default:
		break;
	}
}

//-----------------------------------
//�^�b�N���U��
//-----------------------------------
void Torrent::Tackle()
{

}

//-----------------------------------
//�t���ς��΂��U��
//-----------------------------------
void Torrent::LeafCutter(Location player_location)
{
	CreateLeaf(player_location);
	attack_time--;
	if (attack_time < 0) //�U���̏I��
	{
		leaf_cutter_interval = LEAF_CUTTER_INTERVAL; //���̍U���܂ł̎��Ԃ̐ݒ�
		if (drop_nuts_interval < 0) //�؂̎��𗎂Ƃ��U�����\���ǂ���
		{
			TORRENT_ATTACK next_attack; //���̍U��
			next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) * 2); //���̍U���̐ݒ�

			switch (next_attack) //���̍U���Ɉڍs
			{
			case TORRENT_ATTACK::TACKLE:
				attack_state = TORRENT_ATTACK::TACKLE;
				break;
			case TORRENT_ATTACK::DROP_NUTS:
				attack_state = TORRENT_ATTACK::DROP_NUTS;
				attack_time = DROP_NUTS_TIME;
				break;
			case TORRENT_ATTACK::LEAF_CUTTER:
			case TORRENT_ATTACK::NONE:
			default:
				break;
			}
		}
		else
		{
			attack_state = TORRENT_ATTACK::TACKLE; //�^�b�N���U���Ɉڍs
			if (left_move) //���Ɍ����Ă���
			{
				speed = -TORRENT_SPEED;
			}
			else
			{
				speed = TORRENT_SPEED;
			}
		}
	}
}

//-----------------------------------
//�t���ς̐���
//-----------------------------------
void Torrent::CreateLeaf(Location player_location)
{
	shot_rate++;

	if (shot_rate % TORRENT_TACKLE_DAMAGE == 0)
	{
		BulletManager::GetInstance()->CreateEnemyBullet
		(new TorrentBullet(ENEMY_TYPE::WATER, location, player_location));
	}
}

//-----------------------------------
//�؂̎��𗎂Ƃ��U��
//-----------------------------------
void Torrent::DropNuts()
{
	attack_time--;
	if (attack_time < 0)
	{
		drop_nuts_interval = DROP_NUTS_INTERVAL;

		if (leaf_cutter_interval < 0) //�؂̎��𗎂Ƃ��U�����\���ǂ���
		{
			TORRENT_ATTACK next_attack; //���̍U��
			next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) * 2); //���̍U���̐ݒ�

			switch (next_attack) //���̍U���Ɉڍs
			{
			case TORRENT_ATTACK::TACKLE:
				attack_state = TORRENT_ATTACK::TACKLE;
				break;
			case TORRENT_ATTACK::LEAF_CUTTER:
				attack_state = TORRENT_ATTACK::LEAF_CUTTER;
				attack_time = LEAF_CUTTER_INTERVAL;
				break;
			case TORRENT_ATTACK::DROP_NUTS:
			case TORRENT_ATTACK::NONE:
			default:
				break;
			}
		}
		else
		{
			attack_state = TORRENT_ATTACK::TACKLE; //�^�b�N���U���Ɉڍs
			if (left_move) //���Ɍ����Ă���
			{
				speed = -TORRENT_SPEED;
			}
			else
			{
				speed = TORRENT_SPEED;
			}
		}
	}
}

//-----------------------------------
//�؂̎��̐���
//-----------------------------------
void Torrent::CreateNuts()
{

}

//-----------------------------------
// �U�����Ă��Ȃ�
//-----------------------------------
void Torrent::AttackNone()
{
	TORRENT_ATTACK next_attack;	//���̍U��
	next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) + 1);  //���̍U���̐ݒ�

	switch (next_attack)
	{
	case TORRENT_ATTACK::LEAF_CUTTER:
		attack_state = TORRENT_ATTACK::LEAF_CUTTER;
		attack_time = LEAF_CUTTER_TIME;
		break;
	case TORRENT_ATTACK::DROP_NUTS:
		attack_state = TORRENT_ATTACK::DROP_NUTS;
		attack_time = DROP_NUTS_TIME;
		break;
	case TORRENT_ATTACK::TACKLE:
	case TORRENT_ATTACK::NONE:
	default:
		break;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Torrent::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (attack_state == TORRENT_ATTACK::TACKLE)
	{
		if (!attack)
		{
			attack = true;
			ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::SOIL };
			ret.damage = TORRENT_TACKLE_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}
	}
	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Torrent::Death()
{
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Torrent::HitBullet(const BulletBase* bullet)
{
}

//-----------------------------------
//�`��
//-----------------------------------
void Torrent::Draw() const
{
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Torrent::GetLocation() const
{
	return location;
}