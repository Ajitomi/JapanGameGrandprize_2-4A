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
	down_time = 0;
	attack_interval = 0;
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