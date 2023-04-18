#include "LastBossHand.h"
#include "Player.h"
#include "Stage/Stage.h"

#define HAND_IMAGES

//�ړ����x
#define HAND_MOVE_SPEED 4

//���̃p���`�܂ł̎���
#define PUNCH_INTERVAL 300
//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossHand::LastBossHand(const Location spawn_location, const bool left_hand)
{
	location = spawn_location;

	punch = false;
	attack = false;
	attack_interval = 0; 
	animation = 0; 
	image_argument = 0;

	can_delete = false;
	left_move = left_hand;
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
	if (((location.x - area.width / 2) < player_location.x) &&
		(player_location.x < (location.x + area.width / 2)))
	{
		punch = true;
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

//-----------------------------------
//�p���`
//-----------------------------------
void Punch()
{

}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource LastBossHand::Hit()
{

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