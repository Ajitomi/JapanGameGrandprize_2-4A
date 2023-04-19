#include "LastBossHand.h"
#include "Player.h"
#include "Stage/Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define HAND_IMAGES

//�ړ����x
#define HAND_MOVE_SPEED 4

//���̃p���`�܂ł̎���
#define PUNCH_INTERVAL 300

//�p���`����܂ł̎���
#define PUNCH_STANDBY_TIME 60 

//�p���`�̃X�s�[�h
#define PUNCH_SPEED 8

//�p���`�̃_���[�W
#define PUNCH_DAMAGE 15

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossHand::LastBossHand(const Location spawn_location, const bool left_hand)
{
	location = spawn_location;
	punch_start = location;

	punch = false;
	attack = false;
	attack_interval = 0;
	punch_standby_time = 0;
	animation = 0; 
	image_argument = 0;

	can_delete = false;
	this->left_hand = left_hand;
	left_move = false;
	poison = false;
	paralysis = false;

	damage = 0;
	images = nullptr;
	hp = 1000;
	speed = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	drop_volume = 0;
	drop_type_volume = 0;
	drop_element = nullptr;

	kind = ENEMY_KIND::END_BOSS;
	type = new ENEMY_TYPE[1];
	state = ENEMY_STATE::IDOL;

	hit_block.chip = nullptr;
	hit_block.hit = false;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
LastBossHand::~LastBossHand()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	/*for (int i = 0; i < HAND_IMAGES; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;*/
}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBossHand::Update(const Player* player, const Stage* stage)
{
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

	hit_block = HitStage(stage);

	attack_interval--;
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void LastBossHand::Idol()
{

}

//-----------------------------------
//�ړ�
//-----------------------------------
void LastBossHand::Move(const Location player_location)
{

}

//-----------------------------------
//����
//-----------------------------------
void LastBossHand::Fall()
{

}

//-----------------------------------
//�U��
//-----------------------------------
void LastBossHand::Attack(const Location player_location)
{
	float distance_x; //X���W�̋���
	bool old_punch = punch;

	if (punch) //�p���`���Ă���
	{
		Punch();
	}
	else
	{

		//X���W�̋����̌v�Z
		distance_x = fabsf(location.x - player_location.x);

		//�p���`�͈̔͂ɓ����Ă��čU���̃C���^�[�o�����I����Ă���
		if ((distance_x < area.width / 2) && (attack_interval < 0))
		{
			punch = true;
			punch_standby_time = PUNCH_STANDBY_TIME;
			punch_start = location;
			speed = PUNCH_SPEED;
		}
		else
		{
			if (location.x < player_location.x)
			{
				speed = HAND_MOVE_SPEED;
			}
			else
			{
				speed = -HAND_MOVE_SPEED;
			}

			location.x += speed;
		}
	}

	if (old_punch && (old_punch != punch)) //�p���`�I��
	{
		state = ENEMY_STATE::MOVE;
		attack_interval = PUNCH_INTERVAL;
	}
}

//-----------------------------------
//�p���`
//-----------------------------------
void LastBossHand::Punch()
{
	if (punch_standby_time < 0)
	{
		location.y += speed;
		if (hit_block.hit)
		{
			speed = -PUNCH_SPEED;
		}
	}
	else
	{
		punch_standby_time--;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource LastBossHand::Hit()
{
	AttackResource ret = { 0,nullptr,0 };
	ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::NORMAL };

	if (punch && attack)
	{
		ret.damage = PUNCH_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}
	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void LastBossHand::Death()
{

}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void LastBossHand::HitBullet(const BulletBase* bullet)
{

}

//-----------------------------------
//�ړ����̃A�j���[�V����
//-----------------------------------
void LastBossHand::MoveAnimation()
{

}

//-----------------------------------
//�`��
//-----------------------------------
void LastBossHand::Draw() const
{

}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location LastBossHand::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//�X�V(DotByDot)
//-----------------------------------
void LastBossHand::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void LastBossHand::DebugDraw()
{

}
#endif //_DEBUG