#include "LastBoss.h"
#include "LastBossHand.h"
#include "DxLib.h"
#include "CameraWork.h"

//��̐�
#define HAND_NUM 2

//�_�E�����̗����鑬�x
#define DOWN_MOVE_SPEED 10;

//�_�E�����Ă��鎞��
#define DOWN_TIME 1200

//���@�U��
#define MAGIC_TIME 60 * 30

//���@�̔������[�g
#define MAGIC_RATE 20

//�p���`�U�����Ă��鎞��
#define PUNCH_TIME 60 * 20

//�U���Ԋu
#define ATTACK_INTERVAL 60 * 1

//���̖��@�U���܂ł̎���
#define MAGIC_INTERVAL 60 * 10

//���̃p���`�܂ł̎���
#define PUNCH_INTERVAL 60 * 10


//���̌��U���܂ł̎���
#define SWORD_INTERVAL 60 * 10

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBoss::LastBoss(Location spawn_location)
{
	Location spawn_hand;
	location = spawn_location;

	spawn_hand = location;
	spawn_hand.x -= 200;

	spawn_hand.y += 100;

	hand = new EnemyBase * [HAND_NUM];

	area.height = 200;
	area.width = 200;

	for (int i = 0; i < HAND_NUM; i++)
	{
		spawn_hand.x += (400 * i);
		hand[i] = new LastBossHand(spawn_hand, static_cast<bool>(i));
	}

	kind = ENEMY_KIND::LAST_BOSS;

	down = false;
	attack = false;
	attack_time = 0;
	down_time = 0;
	attack_interval = ATTACK_INTERVAL;
	magic_interval = 0;
	punch_interval = 0;
	sword_interval = 0;

	animation = 0;
	image_argument = 0;

	state = ENEMY_STATE::ATTACK;
	attack_state = LAST_BOSS_ATTACK::NONE;
	hit_stage = { false,nullptr };

}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
LastBoss::~LastBoss()
{
	for (int i = 0; i < HAND_NUM; i++)
	{
		delete hand[i];
	}
	delete[] hand;

}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBoss::Update(const class Player* player, const class Stage* stage)
{
	if (down)
	{
		if (!hit_stage.hit)
		{
			location.y += DOWN_MOVE_SPEED;
		}
		down_time--;
		if (down_time < 0)
		{
			down = false;
		}
	}
	else
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
			Attack(player->GetLocation());
			break;
		case ENEMY_STATE::DEATH:
			break;
		default:
			break;
		}

		for (int i = 0; i < HAND_NUM; i++)
		{
			hand[i]->Update(player, stage);
		}

		if ((hand[0]->GetState() == ENEMY_STATE::DEATH) &&
			(hand[1]->GetState() == ENEMY_STATE::DEATH))
		{
			down = true;
			down_time = DOWN_TIME;
		}

		punch_interval--;
		magic_interval--;
		sword_interval--;
	}
	hit_stage = HitStage(stage);
}

//-----------------------------------
//�_�E������̕��A
//-----------------------------------
bool LastBoss::Revival()
{
	bool ret = false; //�߂�l

	return ret;
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void LastBoss::Idol()
{

}

//-----------------------------------
//�ړ�
//-----------------------------------
void LastBoss::Move(const Location player_location)
{

}

//-----------------------------------
//�ړ����̃A�j���[�V����
//-----------------------------------
void LastBoss::MoveAnimation()
{

}

//-----------------------------------
//����
//-----------------------------------
void LastBoss::Fall()
{

}

//-----------------------------------
//�U��
//-----------------------------------
void  LastBoss::Attack(const Location)
{
	attack_time--;

	switch (attack_state)
	{
	case LAST_BOSS_ATTACK::MAGIC:
		Magic();
		break;
	case LAST_BOSS_ATTACK::PUNCH:
		Punch();
		break;
	case LAST_BOSS_ATTACK::SWORD:
		Sword();
		break;
	case LAST_BOSS_ATTACK::DEATHBLO:
		break;
	case LAST_BOSS_ATTACK::NONE:
		AttackNone();
		break;
	default:
		break;
	}
}

//-----------------------------------
//���@�U���̏�����
//-----------------------------------
void LastBoss::InitMagic()
{
	attack_time = MAGIC_TIME;
}

//-----------------------------------
//���@�U��
//-----------------------------------
void LastBoss::Magic()
{
	attack_time--;
	if (attack_time % MAGIC_RATE == 0)
	{

	}
}

//-----------------------------------
//�p���`�U���̏�����
//-----------------------------------
void LastBoss::InitPunch()
{
	LastBossHand* me_hand;

	attack_state = LAST_BOSS_ATTACK::PUNCH;

	for (int i = 0; i < HAND_NUM; i++)
	{
		me_hand = dynamic_cast<LastBossHand*>(hand[i]);

		me_hand->StartAttack();
	}

	attack_time = PUNCH_TIME;
}

//-----------------------------------
//�p���`�U��
//-----------------------------------
void LastBoss::Punch()
{
	LastBossHand* me_hand;

	if (attack_time < 0)
	{
		for (int i = 0; i < HAND_NUM; i++)
		{
			me_hand = dynamic_cast<LastBossHand*>(hand[i]);

			me_hand->EndAttack();
		}
		attack_state = LAST_BOSS_ATTACK::NONE;
		punch_interval = PUNCH_INTERVAL;
	}
}

//-----------------------------------
//���U���̏�����
//-----------------------------------
void LastBoss::InitSword()
{

}

//-----------------------------------
//���U��
//-----------------------------------
void LastBoss::Sword()
{


}

//-----------------------------------
//�U�����Ȃ�
//-----------------------------------
void LastBoss::AttackNone()
{
	LAST_BOSS_ATTACK next_attack = LAST_BOSS_ATTACK::NONE; //���̍U��
	int attack_num = 0; //�U�����ł����ނ̐�
	attack_interval--;
	if (attack_interval < 0) //�U���\
	{
		if (magic_interval < 0) //���@�U���\
		{
			attack_num++;
		}

		if (punch_interval < 0) //�p���`�U���\
		{
			attack_num++;
		}

		if (sword_interval < 0) //���U���\
		{
			attack_num++;
		}

		if ((attack_num == 3) || (attack_num == 0)) //�U�����ł����ނ̐���3��0��
		{
			next_attack = static_cast<LAST_BOSS_ATTACK>(GetRand(2));
		}
		else if (attack_num == 2) //�U�����ł����ނ̐���2��
		{
			int rand = GetRand(1);

			if ((magic_interval < 0) && (punch_interval < 0)) //���@�U���ƃp���`�U�����\
			{
				next_attack = static_cast<LAST_BOSS_ATTACK>(rand);
			}
			else if((magic_interval < 0) && (sword_interval < 0)) //���@�U���ƌ��U�����\
			{
				next_attack = static_cast<LAST_BOSS_ATTACK>(2 * rand);
			}
			else if ((punch_interval < 0) && (sword_interval < 0)) //�p���`�U���ƌ��U�����\
			{
				next_attack = static_cast<LAST_BOSS_ATTACK>(rand + 1);
			}
			else{}
		}
		else if (attack_num == 1) //�U�����ł����ނ̐���1��
		{
			if (magic_interval < 0) //���@�U���\
			{
				next_attack = LAST_BOSS_ATTACK::MAGIC;
			}
			else if (punch_interval < 0) //�p���`�U���\
			{
				next_attack = LAST_BOSS_ATTACK::PUNCH;
			}
			else if (sword_interval < 0) //���U���\
			{
				next_attack = LAST_BOSS_ATTACK::SWORD;
			}
			else{}
		}
		else{}

		switch (next_attack) //���̍U��
		{
		case LAST_BOSS_ATTACK::MAGIC:
			InitMagic();
			break;
		case LAST_BOSS_ATTACK::PUNCH:
			InitPunch();
			break;
		case LAST_BOSS_ATTACK::SWORD:
			InitSword();
			break;
		case LAST_BOSS_ATTACK::DEATHBLO:
		case LAST_BOSS_ATTACK::NONE:
		default:
			break;
		}
	}

		
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource LastBoss::Hit()
{
	AttackResource ret = { 0,nullptr,0 };

	return ret;
}

//-----------------------------------
//�v���C���[�ƃp���`�Ƃ̓����蔻��
//-----------------------------------
AttackResource LastBoss::PunchAttack(const BoxCollider* player)
{
	AttackResource ret = { 0,nullptr,0 };

	LastBossHand* me_hand;
	for (int i = 0; i < HAND_NUM; i++)
	{
		me_hand = dynamic_cast<LastBossHand*>(hand[i]);

		if (me_hand->IfAttack())
		{
			if (me_hand->HitBox(player))
			{
				ret = me_hand->Hit();
			}
		}
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void LastBoss::Death()
{

}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void LastBoss::HitBullet(const BulletBase* bullet)
{

}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
bool LastBoss::CheckHitBulelt(const BulletBase* bullet)
{
	bool ret = false; //�߂�l

	if (down)
	{
		if (HitSphere(bullet))
		{
			ret = true;
			HitBullet(bullet);
		}
	}

	if (!ret)
	{
		for (int i = 0; i < HAND_NUM; i++)
		{
			if (hand[i]->HitSphere(bullet))
			{
				ret = true;
				hand[i]->HitBullet(bullet);
				break;
			}
		}
	}

	return ret;
}

//-----------------------------------
//�`��
//-----------------------------------
void LastBoss::Draw() const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;
	if (down)
	{
		DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
			draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xffffff, TRUE);
	}
	else
	{
		DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
			draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0x777777, TRUE);
	}

	for (int i = 0; i < HAND_NUM; i++)
	{
		hand[i]->Draw();
	}
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location LastBoss::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//�X�V(DotByDot)
//-----------------------------------
void LastBoss::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void LastBoss::DebugDraw()
{

}
#endif //_DEBUG