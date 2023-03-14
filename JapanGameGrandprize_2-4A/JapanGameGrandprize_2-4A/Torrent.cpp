#include "Torrent.h"
#include "DxLib.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "TorrentBullet.h"
#include "TorrentNuts.h"
#include "BulletManager.h"
#include "CameraWork.h"

//�ړ����x
#define TORRENT_SPEED 4

//�^�b�N���̃_���[�W
#define TORRENT_TACKLE_DAMAGE 10
//�^�b�N����������
#define TPRRENT_TACKLE_PREPARATION 60

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

//�؂̎��̐������鎞��
#define SPAWN_NUTS_INTERVAL 30

//�؂̎��̐����n�_��
#define SPAWN_NUTS_POINT 5

//�؂̎��̃X�|�[���n�_
#define SPAWN_NUTS_Y 100

//�X�|�[���n�_�̊Ԋu
#define NUTS_SPAWN_SPACE 40

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Torrent::Torrent()
{
	left_move = true;
	attack = false;
	tackle_end = false;
	speed = -TORRENT_SPEED;
	tackle_end_point = 0;
	shot_rate = 0;
	leaf_cutter_interval = 0;
	drop_nuts_interval = 0;
	spawn_interval = 0;
	animation = 0;
	image_argument = 0;
	attack_time = 20;
	state = ENEMY_STATE::ATTACK;
	attack_state = TORRENT_ATTACK::NONE;

	/*�����蔻��̐ݒ�*/
	area.width = 160;
	area.height = SCREEN_HEIGHT;
	location.x = SCREEN_WIDTH - area.width / 2;
	location.y = SCREEN_HEIGHT + SCREEN_HEIGHT / 2;

	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::SOIL;
	kind = ENEMY_KIND::TORRENT;

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

	delete[] type;
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
	if (attack_time < 0)
	{
		location.x += speed;

		Location scroll; //��ʃX�N���[�����l���������W
		Location camera = CameraWork::GetCamera(); //�J����
		scroll = location - camera;

		if (left_move)
		{
			if (scroll.x <= tackle_end_point)
			{
				tackle_end = true;
				left_move = !left_move;
			}
		}
		else
		{
			if (tackle_end_point <= scroll.x)
			{
				tackle_end = true;
				left_move = !left_move;
			}
		}
		
		if (tackle_end) //�^�b�N���I��
		{
			attack = false;
			TORRENT_ATTACK next_attack;	//���̍U��
			if (leaf_cutter_interval < 0 && drop_nuts_interval < 0) //2�̍U�����\�Ȏ�
			{
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
			else if(leaf_cutter_interval < 0) //�t���ς��΂��U���������\�Ȏ�
			{
				attack_state = TORRENT_ATTACK::LEAF_CUTTER;
				attack_time = LEAF_CUTTER_TIME;
			}
			else if (drop_nuts_interval < 0) //�؂̎����΂��U�����\�Ȏ�
			{
				attack_state = TORRENT_ATTACK::DROP_NUTS;
				attack_time = DROP_NUTS_TIME;
			}
			else //�ǂ���̍U�����\����Ȃ��Ƃ�
			{
				if (leaf_cutter_interval < drop_nuts_interval)
				{
					attack_state = TORRENT_ATTACK::LEAF_CUTTER;
					attack_time = LEAF_CUTTER_TIME;
				}
				else
				{
					attack_state = TORRENT_ATTACK::DROP_NUTS;
					attack_time = DROP_NUTS_TIME;
				}
			}
		}
	}
	else
	{
		attack_time--;
	}
}

//-----------------------------------
//�t���ς��΂��U��
//-----------------------------------
void Torrent::LeafCutter(Location player_location)
{
	attack_time--;
	CreateLeaf(player_location);
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
				attack_time = TPRRENT_TACKLE_PREPARATION;
				tackle_end = false;
				if (left_move) //���Ɍ����Ă���
				{
					speed = -TORRENT_SPEED;
					tackle_end_point = 0 + area.width / 2;
				}
				else
				{
					speed = TORRENT_SPEED;
					tackle_end_point = SCREEN_WIDTH - area.width / 2;
				}
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
			attack_time = TPRRENT_TACKLE_PREPARATION;
			tackle_end = false;
			if (left_move) //���Ɍ����Ă���
			{
				speed = -TORRENT_SPEED;
				tackle_end_point = 0 + area.width / 2;
			}
			else
			{
				speed = TORRENT_SPEED;
				tackle_end_point = SCREEN_WIDTH - area.width / 2;
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

	if (shot_rate % TORRENT_SHOT_RATE == 0) //�t���ς̐���
	{
		Location spawn_location = location; //�������W
		spawn_location.y = location.y - area.height / 2;
		BulletManager::GetInstance()->
			CreateEnemyBullet(new TorrentBullet(ENEMY_TYPE::WIND, spawn_location, player_location));
	}
}

//-----------------------------------
//�؂̎��𗎂Ƃ��U��
//-----------------------------------
void Torrent::DropNuts()
{
	attack_time--;
	CreateNuts();
	if (attack_time < 0)
	{
		drop_nuts_interval = DROP_NUTS_INTERVAL;
		spawn_interval = 0;
		if (leaf_cutter_interval < 0) //�؂̎��𗎂Ƃ��U�����\���ǂ���
		{
			TORRENT_ATTACK next_attack; //���̍U��
			next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) * 2); //���̍U���̐ݒ�

			switch (next_attack) //���̍U���Ɉڍs
			{
			case TORRENT_ATTACK::TACKLE:
				attack_state = TORRENT_ATTACK::TACKLE;
				attack_time = TPRRENT_TACKLE_PREPARATION;
				tackle_end = false;
				if (left_move) //���Ɍ����Ă���
				{
					speed = -TORRENT_SPEED;
					tackle_end_point = 0 + area.width / 2;
				}
				else
				{
					speed = TORRENT_SPEED;
					tackle_end_point = SCREEN_WIDTH - area.width / 2;
				}
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
			attack_time = TPRRENT_TACKLE_PREPARATION;
			tackle_end = false;
			if (left_move) //���Ɍ����Ă���
			{
				speed = -TORRENT_SPEED;
				tackle_end_point = 0 + area.width / 2;
			}
			else
			{
				speed = TORRENT_SPEED;
				tackle_end_point = SCREEN_WIDTH - area.width / 2;
			}
		}
	}
}

//-----------------------------------
//�؂̎��̐���
//-----------------------------------
void Torrent::CreateNuts()
{
	bool spawn_point[SPAWN_NUTS_POINT]; //�X�|�[���n�_
	int spawn_volume = 0; //�X�|�[����
	bool spawn = false; //�X�|�[������

	spawn_interval++;
	
	if (spawn_interval % SPAWN_NUTS_INTERVAL == 0)
	{
		for (int i = 0; i < SPAWN_NUTS_POINT; i++)
		{
			spawn_point[i] = false;
		}

		spawn_volume = GetRand(SPAWN_NUTS_POINT - 1) + 1; //�X�|�[�����̐ݒ�

		for (int i = 0; i < spawn_volume; i++) //�؂̎��̐���
		{
			spawn = false;

			while (!spawn)
			{
				int spawn_point_rand; //�X�|�[���n�_
				spawn_point_rand = GetRand(SPAWN_NUTS_POINT - 1); //�X�|�[���n�_�̐ݒ�
				if (!spawn_point[spawn_point_rand])
				{
					Location spawn_location; //�X�|�[���n�_
					spawn_location.x = ((spawn_point_rand + 1) * NUTS_SPAWN_SPACE);
					if (!left_move)
					{
						spawn_location.x += (area.width / 2);
					}
					spawn_location.y = SPAWN_NUTS_Y;
					spawn_point[spawn_point_rand] = true;
					spawn = true;

					BulletManager::GetInstance()->
						CreateEnemyNuts(new TorrentNuts(ENEMY_TYPE::WATER, spawn_location));
				}

			}
		}
	}
	

}

//-----------------------------------
// �U�����Ă��Ȃ�
//-----------------------------------
void Torrent::AttackNone()
{
	attack_time--;
	if (attack_time < 0)
	{
		TORRENT_ATTACK next_attack;	//���̍U��
		next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) + 1);  //���̍U���̐ݒ�
		
		next_attack = TORRENT_ATTACK::DROP_NUTS;
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
	Location draw_location = location; //�`����W
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xffffff, TRUE);
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Torrent::GetLocation() const
{
	return location;
}