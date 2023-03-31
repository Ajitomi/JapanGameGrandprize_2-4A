#include "Dragon.h"
#include "CameraWork.h"
#include "DxLib.h"

//�h���S���̉摜�T�C�Y(����A�摜���o�����撲���j
#define DRAGON_SIZE_X 40
#define DRAGON_SIZE_Y 80

//���@�U���������̍d������
#define MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define PHYSICAL_STANDBY 100

//�h���S���̍U����
#define ATTACK_DAMAGE 20F  //float�^

//�h���b�v��(�ŏ�)
#define MIN_DROP 40

//�h���b�v��(�ő�)
#define MAX_DROP 60

Dragon::Dragon(Location spawn_location)
{
	location = spawn_location;

	animation = 0;
	animation_time = 0;
	hp = 500; 	
	speed = 0; 

	can_delete = false;
	left_move = true;

	kind = ENEMY_KIND::DRAGON;
	type = new ENEMY_TYPE[3];
	type[0] = ENEMY_TYPE::FIRE;
	type[1] = ENEMY_TYPE::WIND;
	type[2] = ENEMY_TYPE::THUNDER;

	state = ENEMY_STATE::IDOL;

	attack_state = DRAGON_ATTACK::NONE;

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [THUNDER_DROP];
	drop_type_volume = THUNDER_DROP;

	int volume = 0;
	for (int i = 0; i < THUNDER_DROP; i++)
	{
		volume = MIN_DROP + GetRand(MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
}

Dragon::~Dragon()
{
	delete[] type;

	for (int i = 0; i < THUNDER_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

void Dragon::Update(const class Player* player, const class Stage* stage)
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
		STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
		hit_direction = HitDirection(hit_stage.chip);

		if (hit_direction == STAGE_DIRECTION::TOP)
		{
			location = old_location;
		}
		if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
		{
			location = old_location;
			left_move = !left_move;
		}

	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}

//-----------------------------------
//�`��
//-----------------------------------
void Dragon::Draw() const
{

}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Dragon::Idol()
{

}

//-----------------------------------
//����
//-----------------------------------
void Dragon::Move(const Location player_location)
{

}

//-----------------------------------
//�U��
//-----------------------------------
void Dragon::Attack(const Location player_location)
{
	switch (attack_state)
	{
		
	case DRAGON_ATTACK::DITE://���݂�
		DiteMove(player_location);
		break;
	case DRAGON_ATTACK::TAIL_ATTACK: //�K���U��
		TailMove(player_location);
		break;
	case DRAGON_ATTACK::DREATH: //�u���X�U��
		DreathMove(player_location);
		break;
	case DRAGON_ATTACK::ROAR: //���K������ɗ����~�点��
		RoarMove(player_location);
		break;
	case DRAGON_ATTACK::NONE:
	default:
		break;
	}
}

//-----------------------------------
//�ڋߍU�����̊��݂�
//-----------------------------------
void Dragon::DiteMove(const Location player_location)
{

}

//-----------------------------------
//�ڋߍU�����̊��݂�
//-----------------------------------
void Dragon::TailMove(const Location player_location)
{

}

//-----------------------------------
//�������U���i�u���X�j
//-----------------------------------
void Dragon::DreathMove(const Location player_location)
{

}


void Dragon::RoarMove(const Location player_location)
{

}

//-----------------------------------
//�U�������������̂�
//-----------------------------------
AttackResource Dragon::Hit()
{
	return AttackResource();
}

//-----------------------------------
//����
//-----------------------------------
void Dragon::Fall()
{

}

//-----------------------------------
//���S�i�|���ꂽ�j
//-----------------------------------
void Dragon::Death()
{

}

//-----------------------------------
//�v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void Dragon::HitBullet(const BulletBase* bullet)
{

}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Dragon::GetLocation() const
{
	return Location();
}


#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void Dragon::Update(const ENEMY_STATE state)
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
void Dragon::DebugDraw()
{
	
}
#endif //_DEBUG