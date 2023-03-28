#include "Harpy.h"
#include "CameraWork.h"
#include "BulletManager.h"
#include "DxLib.h"

//�n�[�s�B�̉摜�T�C�Y(����A�摜���o�����撲���j
#define HARPY_SIZE_X 40
#define HARPY_SIZE_Y 80

//�v���C���[��������
#define DETECTION_DISTANCE 600
#define DETECTION_DISTANCE_Y 250

//�U���͈�
#define ATTACK_RANGE 150

//���@�U���������̍d������
#define MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define PHYSICAL_STANDBY 100

//�n�[�s�B�̍U����
#define HARPY_ATTACK_DAMAGE 4

//�ړ��X�s�[�h
#define SPEED 2.5

//�U���X�s�[�h
#define ATTACK_SPEED 5

//�h���b�v��(�ŏ�)
#define HARPY_MIN_DROP 1

//�h���b�v��(�ő�)
#define HARPY_DROP 6

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Harpy::Harpy(Location spawn_location)
{

	can_delete = false;
	left_move = true;
	attack = false;

	hp = 50;
	physical_time = 0;
	magic_num = 0;
	magic_time = 1;
	location = spawn_location;
	standby_attack = 0;
	travel = 0;
	travel_y = 0;
	range = 0;
	range_y = 0;
	vector = 0;
	speed = SPEED;
	area.width = HARPY_SIZE_X;
	area.height = HARPY_SIZE_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;

	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	inversion = false;
	kind = ENEMY_KIND::HARPY;

	//harpy_image = LoadGraph("Images/Enemy/???????.png"); //�摜�Ǎ���
	harpy_image = 0; //�摜�����炢�����L�̏����ɕύX

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;
	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = HARPY_MIN_DROP + GetRand(HARPY_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::WIND;
	attack_state = HARPY_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = HARPY_STATE::NORMAL;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Harpy::~Harpy()
{

	delete[] images;
	delete[] type;

	for (int i = 0; i < WIND_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void Harpy::Update(const class Player* player, const class Stage* stage)
{

	Location old_location = location;	//�O�̍��W
	HitMapChip hit_stage = { false,nullptr }; //�X�e�[�W�Ƃ̓����蔻��

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
		if (physical_attack == true)
		{
			PhysicalMove(player->GetLocation());
		}
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}

	hit_stage = HitStage(stage);
	if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
	{
		Location chip_location = hit_stage.chip->GetLocation();
		Area chip_area = hit_stage.chip->GetArea();
		if ((chip_location.y + chip_area.height / 2) < (location.y + area.height / 2))
		{
			//���x�𗎂Ƃ����������́A���]�����鏈�����쐬
			location = old_location;
			/*if (left_move ==true)
			{
				left_move = false;
			}
			else
			{
				left_move = false;
			}*/
		}

	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}

//�A�C�h�����
void Harpy::Idol()
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

//�ړ�
void Harpy::Move(const Location player_location)
{

	//�v���C���[�Ƃ̋����v�Z
	range = player_location.x - location.x;
	range_y = player_location.y - location.y;


	//�v���C���[�������������ɂ�����
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE &&
		range_y <= DETECTION_DISTANCE_Y && range_y >= -DETECTION_DISTANCE_Y)
	{
		//�ڋߍU��
		if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE || magic_num > 4)
		{

			state = ENEMY_STATE::ATTACK;
			attack_state = HARPY_ATTACK::PHYSICAL_ATTACK;
			standby_time = PHYSICAL_STANDBY;
			physical_attack = true;

		}
		//�������U��
		else
		{

			state = ENEMY_STATE::ATTACK;
			attack_state = HARPY_ATTACK::MAGIC_ATTACK;
			standby_time = MAGIC_STANDBY;
			magic_attack = true;

			//���ˊԊu
			if (magic_time++ % 2 == 0)
			{
				//�e�̐���
				magic_num++;
				BulletManager::GetInstance()->CreateEnemyBullet
				(new HarpyBullet(location, player_location));
			}
		}
	}
	else //���������Ƀv���C���[�����Ȃ�������B�ʏ�ړ�
	{
		if (left_move == true)
		{
			action_type = HARPY_STATE::NORMAL; //��
		}
		else
		{
			action_type = HARPY_STATE::NORMAL_RIGHT; //�E
		}
		switch (action_type)
		{
		case HARPY_STATE::NORMAL:  //�ʏ�ړ�
			location.x -= speed;
			break;
		case HARPY_STATE::NORMAL_RIGHT://�E
			location.x += speed;
			break;
		case HARPY_STATE::NONE:
			break;
		default:
			break;
		}
	}
}

//-----------------------------------
//�U��
//-----------------------------------
void  Harpy::Attack(Location player_location)
{

	standby_time--;
	if (standby_time < 0)
	{
		switch (attack_state)
		{
		case HARPY_ATTACK::PHYSICAL_ATTACK:
			attack = false;
			physical_attack = false;
			attack_state = HARPY_ATTACK::NONE;
			break;
		case HARPY_ATTACK::MAGIC_ATTACK:
			magic_attack = false;
			break;
		case HARPY_ATTACK::NONE:
			break;
		default:
			break;
		}
		standby_time = 0;
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Harpy::Hit()
{

	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (attack_state == HARPY_ATTACK::PHYSICAL_ATTACK && (!attack))
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = HARPY_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Harpy::Death()
{

	can_delete = true;
}

//-----------------------------------
// �`��
//-----------------------------------
void Harpy::Draw()const
{

	//�X�N���[���ɍ��킹�ĕ`��
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);
}

//-----------------------------------
//����
//-----------------------------------
void Harpy::Fall()
{

}

//-----------------------------------
// �v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void Harpy::HitBullet(const BulletBase* bullet)
{

	switch (bullet->GetAttribute()) //�󂯂��������̑���
	{
	case ATTRIBUTE::NORMAL: //�ʏ�e 
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE; //�����ɂ���
		break;
	case ATTRIBUTE::EXPLOSION: //���� 
		hp -= bullet->GetDamage(); //�ʏ�
		break;
	case ATTRIBUTE::MELT: //�n���� 
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE; //�����ɂ���
		break;
	case ATTRIBUTE::POISON: //�Ł@��_
		if (!poison)
		{
			poison = true;
			poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
			poison_damage = bullet->GetDamage();
		}
		break;
	case ATTRIBUTE::PARALYSIS: //��� ��_
		if (!paralysis)
		{
			paralysis = true;
			paralysis_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;  //��_
		}
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}
}

//-----------------------------------
//�ڋߍU���i�����U���j���̓���
//-----------------------------------
void Harpy::PhysicalMove(const Location player_location)
{

	range = player_location.x - location.x;
	range_y = player_location.y - location.y;

	vector = sqrt(range * range + range_y * range_y);

	travel = range / vector;
	travel_y = range_y / vector;
	location.x += travel * speed;
	location.y += travel_y * speed;

	if (physical_time++ % 5 == 0)
	{
		magic_num = 0;
	}
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Harpy::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void Harpy::Update(const ENEMY_STATE state)
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
void Harpy::DebugDraw()
{
	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xffffff, FALSE);
}
#endif //_DEBUG