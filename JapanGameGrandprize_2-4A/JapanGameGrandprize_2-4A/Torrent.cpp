#include "Torrent.h"
#include "DxLib.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "TorrentBullet.h"
#include "TorrentNuts.h"
#include "BulletManager.h"
#include "CameraWork.h"

//�摜����
#define TORRENT_IMAGES 27

//�ړ����x
#define TORRENT_SPEED 8

//�^�b�N���̃_���[�W
#define TORRENT_TACKLE_DAMAGE 20

//�̗�
#define TORRENT_HP 1000

//�^�b�N����������
#define TORRENT_TACKLE_PREPARATION 60

//���ˑ��x
#define TORRENT_SHOT_RATE 15

//�h���b�v��
#define TORRENT_MIN_DROP 20
#define TORRENT_DROP 20

//�t���ς��΂��Ă��鎞��
#define LEAF_CUTTER_TIME 420

//���̗t���ς��΂��U���Ɉڂ鎞��
#define LEAF_CUTTER_INTERVAL 300

//�؂̎��𗎂Ƃ��Ă��鎞��
#define DROP_NUTS_TIME 600

//���̖؂̎��𗎂Ƃ��U���Ɉڂ鎞��
#define DROP_NUTS_INTERVAL 300

//�؂̎��̐������鎞��
#define SPAWN_NUTS_INTERVAL 30

//�؂̎��̐����n�_��
#define SPAWN_NUTS_POINT 15

//�؂̎������ŃX�|�[���ł���ő吔
#define SPAWN_NUTS_MAX 6

//�؂̎��̃X�|�[���n�_
#define SPAWN_NUTS_Y 100

//�X�|�[���n�_�̊Ԋu
#define NUTS_SPAWN_SPACE 80

//�A�j���[�V����
#define TORRENT_ANIMATION 5


int Torrent::torrent_falling_nut_se = 0;   //�؂̎������鉹
int Torrent::torrent_tackle_se = 0;        //�^�b�N��
int Torrent::torrent_leaves_cutter = 0;    //�t���ϔ�΂�


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Torrent::Torrent(Location spawn_location)
{
	//��hp
	hp = TORRENT_HP;
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
	state = ENEMY_STATE::MOVE;
	attack_state = TORRENT_ATTACK::NONE;

	/*�����蔻��̐ݒ�*/
	area.width = 180;
	area.height = 300;
	location = spawn_location;

	location.x += MAP_CHIP_SIZE * 10;
	location.y += MAP_CHIP_SIZE / 2;

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

	int num = static_cast<int>(kind) - static_cast<int>(ENEMY_KIND::SLIME);

	if (images[num].empty())
	{
		images[num].resize(TORRENT_IMAGES);

		LoadDivGraph("Images/Enemy/torrent_tackle.png", 8, 8, 1, 500, 500, &images[num][0]);
		LoadDivGraph("Images/Enemy/torrent_nut.png", 9, 9, 1, 500, 500, &images[num][8]);
		LoadDivGraph("Images/Enemy/torrent_leaf.png", 10, 10, 1, 500, 500, &images[num][17]);
	}
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Torrent::~Torrent()
{
	DeleteGraph(magic_circle_image);

	for (int i = 0; i < WIND_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

//-----------------------------------
//�X�V
//-----------------------------------
void Torrent::Update(const Player* player, const Stage* stage)
{
	animation++;
	Location old_location = location;	//�O�̍��W


	Location scroll; //��ʃX�N���[�����l���������W
	Location camera = CameraWork::GetCamera(); //�J����
	scroll = location - camera;

	if (SCREEN_WIDTH < scroll.x + area.width / 2 + speed)
	{
		state = ENEMY_STATE::MOVE;
	}
	else if (state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::ATTACK;
	}

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

	Animation();
	UpdateDamageLog();
	Poison();
	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
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
	location.x += static_cast<float>(speed);
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

	leaf_cutter_interval--;
	drop_nuts_interval--;


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

		if (left_move)
		{
			if (location.x <= tackle_end_point)
			{
				tackle_end = true;
				left_move = !left_move;
			}
		}
		else
		{
			if (tackle_end_point <= location.x)
			{
				tackle_end = true;
				left_move = !left_move;
			}
		}

		if (tackle_end) //�^�b�N���I��
		{
			attack = false;
			int next_attack;	//���̍U��
			next_attack = GetRand(10) + 1;  //���̍U���̐ݒ�

			if (7 < next_attack)
			{
				if (drop_nuts_interval < leaf_cutter_interval)
				{
					attack_state = TORRENT_ATTACK::DROP_NUTS;
					attack_time = DROP_NUTS_TIME;
				}
				else
				{
					attack_state = TORRENT_ATTACK::LEAF_CUTTER;
					attack_time = LEAF_CUTTER_TIME;
				}
			}
			else
			{
				if (drop_nuts_interval < leaf_cutter_interval)
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
			
			
			image_argument = 0;

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
void Torrent::LeafCutter(const Location player_location)
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
				attack_time = TORRENT_TACKLE_PREPARATION;
				tackle_end = false;
				tackle_end_point = CameraWork::GetCamera().x;
				if (left_move) //���Ɍ����Ă���
				{
					speed = -TORRENT_SPEED;
					tackle_end_point += static_cast<int>(area.width / 2) + MAP_CHIP_SIZE;
				}
				else
				{
					speed = TORRENT_SPEED;
					tackle_end_point += static_cast<int>(SCREEN_WIDTH - area.width / 2) - MAP_CHIP_SIZE;
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
			image_argument = 0;
		}
		else
		{
			attack_state = TORRENT_ATTACK::TACKLE; //�^�b�N���U���Ɉڍs
			attack_time = TORRENT_TACKLE_PREPARATION;
			tackle_end = false;
			tackle_end_point = CameraWork::GetCamera().x;

			if (left_move) //���Ɍ����Ă���
			{
				speed = -TORRENT_SPEED;
				tackle_end_point += static_cast<int>(area.width / 2) + MAP_CHIP_SIZE;
			}
			else
			{
				speed = TORRENT_SPEED;
				tackle_end_point += static_cast<int>(SCREEN_WIDTH - area.width / 2) - MAP_CHIP_SIZE;
			}
			image_argument = 0;
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
			CreateEnemyBullet(new TorrentBullet(spawn_location, player_location));
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
				attack_time = TORRENT_TACKLE_PREPARATION;
				tackle_end = false;
				tackle_end_point = CameraWork::GetCamera().x;

				if (left_move) //���Ɍ����Ă���
				{
					speed = -TORRENT_SPEED;
					tackle_end_point += static_cast<int>(area.width / 2) + MAP_CHIP_SIZE;
				}
				else
				{
					speed = TORRENT_SPEED;
					tackle_end_point += static_cast<int>(SCREEN_WIDTH - area.width / 2) - MAP_CHIP_SIZE;
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
			attack_time = TORRENT_TACKLE_PREPARATION;
			tackle_end = false;
			tackle_end_point = CameraWork::GetCamera().x;

			if (left_move) //���Ɍ����Ă���
			{
				speed = -TORRENT_SPEED;
				tackle_end_point += static_cast<int>(area.width / 2) + MAP_CHIP_SIZE;
			}
			else
			{
				speed = TORRENT_SPEED;
				tackle_end_point += static_cast<int>(SCREEN_WIDTH - area.width / 2) - MAP_CHIP_SIZE;
			}
		}
		image_argument = 0;
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

		spawn_volume = GetRand(SPAWN_NUTS_MAX - 1) + 1; //�X�|�[�����̐ݒ�

		for (int i = 0; i < spawn_volume; i++) //�؂̎��̐���
		{
			spawn = false;

			while (!spawn)
			{
				int spawn_point_rand; //�X�|�[���n�_
				spawn_point_rand = GetRand(SPAWN_NUTS_POINT - 1); //�X�|�[���n�_�̐ݒ�
				if (!spawn_point[spawn_point_rand])
				{
					Location spawn_location = CameraWork::GetCamera(); //�X�|�[���n�_
					spawn_location.x += (spawn_point_rand + 1) * NUTS_SPAWN_SPACE;
					
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
		next_attack = static_cast<TORRENT_ATTACK>(GetRand(1) + 1);  //���̍U���̐ݒ�

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
		image_argument = 0;
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

	can_delete = true;
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Torrent::HitBullet(const BulletBase* bullet)
{
	PlayHitBulletSound(bullet->GetAttribute());

	int i;
	int damage = 0;
	for (i = 0; i < LOG_NUM; i++)
	{
		if (!damage_log[i].log)
		{
			break;
		}
	}

	if (LOG_NUM <= i)
	{
		for (i = 0; i < LOG_NUM - 1; i++)
		{
			damage_log[i] = damage_log[i + 1];
		}
		i = LOG_NUM - 1;

	}

	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;

		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage() * 0;
		damage_log[i].congeniality = CONGENIALITY::INVALID;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage() * WEAKNESS_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::WEAKNESS;
		break;
	case ATTRIBUTE::POISON:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		if (!poison)
		{
			poison_damage = bullet->GetDamageParSecond();
			poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = bullet->GetDamage();
	case ATTRIBUTE::HEAL:
	default:
		break;
	}

	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
	hp -= damage;

	if (hp < 0)
	{
		hp = 0;
	}
}

//-----------------------------------
//�^�b�N���̃A�j���[�V����
//-----------------------------------
void Torrent::Animation()
{
	if (animation % TORRENT_ANIMATION == 0)
	{
		image_argument++;
	}
}


//----------------------------------------
// SE�ǂݍ���
//----------------------------------------
void Torrent::LoadSounds()
{
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	torrent_falling_nut_se = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/TorrentAttack4.wav", 8);
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);

	torrent_tackle_se = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/TorrentAttack2.wav");
	torrent_leaves_cutter = LoadSoundMem("Sounds/SE/Stage/EnemyAttack/TorrentAttack3.wav");
}



//-----------------------------------
//�`��
//-----------------------------------
void Torrent::Draw() const
{
	Location draw_location = location; //�`����W
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	int num = static_cast<int>(kind) - static_cast<int>(ENEMY_KIND::SLIME);

	if (state == ENEMY_STATE::MOVE)
	{
		DrawRotaGraphF(draw_location.x, draw_location.y, 0.7, 0, images[num][image_argument % 8], TRUE, !left_move);
	}
	else
	{
		switch (attack_state)
		{
		case TORRENT_ATTACK::TACKLE:
			DrawRotaGraphF(draw_location.x, draw_location.y, 0.7, 0, images[num][image_argument % 8], TRUE, !left_move);
			break;
		case TORRENT_ATTACK::LEAF_CUTTER:
			DrawRotaGraphF(draw_location.x, draw_location.y, 0.7, 0, images[num][image_argument % 10 + 17], TRUE, !left_move);
			break;
		case TORRENT_ATTACK::DROP_NUTS:
			DrawRotaGraph3(SCREEN_WIDTH / 2, 50, 640, 640, 1, 0.05, 0, magic_circle_image, TRUE);
			DrawRotaGraphF(draw_location.x, draw_location.y, 0.7, 0, images[num][image_argument % 9 + 8], TRUE, !left_move);
			break;
		case TORRENT_ATTACK::NONE:
			DrawRotaGraphF(draw_location.x, draw_location.y, 0.7, 0, images[num][0], TRUE, !left_move);
			break;
		default:
			break;
		}
	}

	//��ʓ��ɉf���Ă���HP��`�悷��
	if (state != ENEMY_STATE::DEATH && draw_location.x + area.width / 2 < SCREEN_WIDTH + MAP_CHIP_SIZE)
	{
		DrawHPBar(TORRENT_HP);
		DrawDamageLog();
		DrawWeaknessIcon();
	}
	
}

//-----------------------------------
//HP�o�[�̕`��
//-----------------------------------
void Torrent::DrawHPBar(const int max_hp) const
{
	int color = GetColor(7, 255, 0);

	if (hp <= (max_hp / 2))
	{
		color = GetColor(255, 255 * static_cast<float>(hp) / max_hp, 0);
	}
	else
	{
		color = GetColor(7 + 2 * (248 * (1 - static_cast<float>(hp) / max_hp)), 255, 0);
	}

	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x000000, TRUE);
	DrawBox(160, 10, 160 + (960 * (static_cast<float>(hp) / max_hp)), 40, color, TRUE);
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x8f917f, FALSE);
}


//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Torrent::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void Torrent::Update(const ENEMY_STATE state)
{
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}
}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void Torrent::DebugDraw()
{
	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xff0000, FALSE);
}
#endif //_DEBUG