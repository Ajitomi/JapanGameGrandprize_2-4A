#include "Harpy.h"
#include "CameraWork.h"

//�n�[�s�B�̉摜�T�C�Y(����A�摜���o�����撲���j
#define HARPY_SIZE_X 40
#define HARPY_SIZE_Y 80

//�v���C���[��������
#define HARPY_DETECTION_DISTANCE 500

//�����U���͈�
#define HARPY_ATTACK_RANGE 20

//���@�U���͈�	
#define HARPY_ATTACK_MAGIC 400

//���@�U���������̍d������
#define HARPY_MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define HARPY_PHYSICAL_STANDBY 100

//�n�[�s�B�̍U����
#define HARPY_ATTACK_DAMAGE 4

//�ړ��X�s�[�h
#define HARPY_SPEED 2.5

//�U���X�s�[�h
#define ATTACK_SPEED 5

//�h���b�v��(�ŏ�)
#define HARPY_MIN_DROP 0u

//�h���b�v��(�ő�)
#define HARPY_MAX_DROP 4u


//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Harpy::Harpy()
{
	can_delete = false;
	left_move = true;
	attack = false;

	hp = 10;
	location.x = 1400;
	location.y = 1050;
	standby_attack = 0;
	speed = 1.5;
	area.width = HARPY_SIZE_X;
	area.height = HARPY_SIZE_Y;
	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	inversion = false;
	kind = ENEMY_KIND::GHOST;

	//harpy_image = LoadGraph("Images/Enemy/???????.png"); //�摜�Ǎ���
	harpy_image = 0; //�摜�����炢�����L�̏����ɕύX

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;
	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = HARPY_MIN_DROP + GetRand(HARPY_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = HARPY_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = HARPY_STATE::NORMAL;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Harpy::~Harpy()
{

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
			speed = 0.1;
		}
		else
		{
			speed = 1.5;
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

	switch (action_type)
	{
	case HARPY_STATE::NORMAL:  //�ʏ�ړ�
		location.x -= speed;
		break;
	case HARPY_STATE::NORMAL_RIGHT://�E
		location.x += speed;
		break;
	case HARPY_STATE::LEFT_lOWER:  //������ڎw��
		location.x -= speed;
		location.y += speed;
		break;
	case HARPY_STATE::LEFT_UPPER:  //�����ڎw��
		location.x -= speed;
		location.y -= speed;
		break;
	case HARPY_STATE::RIGHT_LOWER:  //�E����ڎw��
		location.x += speed;
		location.y += speed;
		break;
	case HARPY_STATE::RIGHT_UPPER:  //�E���ڎw���B
		location.x += speed;
		location.y -= speed;
		break;
	default:
		break;
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


	//DrawRotaGraph(draw_location.x, draw_location.y, 1.5f, M_PI / 180, ghost_image, TRUE);
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
		poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
		poison_damage = bullet->GetDamage();
		break;
	case ATTRIBUTE::PARALYSIS: //��� ��_
		paralysis_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;  //��_
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Harpy::GetLocation() const
{
	return location;
}