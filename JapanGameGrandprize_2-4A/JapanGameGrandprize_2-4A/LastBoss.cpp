#include "LastBoss.h"
#include "LastBossHand.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "LastBossMagic.h"

//�̗�
#define LAST_BOSS_HP 5000

//��̐�
#define HAND_NUM 2

//���@�̔�����
#define MAGIC_NUM1 2
#define MAGIC_NUM2 3
#define MAGIC_NUM3 4


//�_�E�����̗����鑬�x
#define DOWN_MOVE_SPEED 10

//�_�E�����Ă��鎞��
#define DOWN_TIME 60 * 10

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

//�K�E�Z�̎���
#define SPECIAL_MOVES_TIME 60 * 10

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBoss::LastBoss(Location spawn_location)
{
	Location spawn_hand;
	this->spawn_location = spawn_location;
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

	magic = nullptr;

	kind = ENEMY_KIND::LAST_BOSS;

	special_moves = false;
	down = false;
	attack = false;
	attack_time = 0;
	down_time = 0;
	attack_interval = ATTACK_INTERVAL;
	magic_interval = 0;
	punch_interval = 0;
	sword_interval = 0;
	magic_rate = 0;
	magic_volume = 0;
	special_moves_time = 0;
	hp = LAST_BOSS_HP;
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

	for (int i = 0; i < magic_volume; i++)
	{
		delete magic;
	}
	delete[] magic;
}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBoss::Update(const class Player* player, const class Stage* stage)
{
	LastBossHand* me_hand;

	if (down)
	{
		down_time--;
		if (down_time < 0)
		{
			if (Revival())
			{
				down = false;
				for (int i = 0; i < HAND_NUM; i++)
				{
					me_hand = dynamic_cast<LastBossHand*>(hand[i]);

					me_hand->Revival();
				}
			}
		}
		else
		{
			if (!hit_stage.hit)
			{
				location.y += DOWN_MOVE_SPEED;
			}
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

	UpdateDamageLog();

	if ((hp <= 1) && (!special_moves))
	{
		hp = 1;
		special_moves = true;
		attack_state = LAST_BOSS_ATTACK::SPECIAL_MOVES;
	}
}

//-----------------------------------
//�_�E������̕��A
//-----------------------------------
bool LastBoss::Revival()
{
	bool ret = false; //�߂�l

	location.y -= DOWN_MOVE_SPEED / 2;

	if (spawn_location == location)
	{
		ret = true;
	}

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
	case LAST_BOSS_ATTACK::SPECIAL_MOVES:
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
	if(hp < (LAST_BOSS_HP / 3)) //���@�̔������̐ݒ�
	{
		magic_volume = MAGIC_NUM3;
	}
	else if (hp < ((LAST_BOSS_HP / 3) * 2))
	{
		magic_volume = MAGIC_NUM2;
	}
	else
	{
		magic_volume = MAGIC_NUM1;
	}
	magic = new EnemyBulletBase * [magic_volume];

	attack_state = LAST_BOSS_ATTACK::MAGIC;


}

//-----------------------------------
//���@�U��
//-----------------------------------
void LastBoss::Magic()
{
	attack_time--;
	if (attack_time % MAGIC_RATE == 0)
	{
		for (int i = 0; i < magic_volume; i++)
		{
			if (magic[i] == nullptr)
			{
				Location magic_location;
				magic_location.x = GetRand(SCREEN_WIDTH - MAGIC_AREA * 2) + MAGIC_AREA;
				magic_location.y = GetRand(SCREEN_HEIGHT - MAGIC_AREA * 2) + MAGIC_AREA;

				magic[i] = new LastBossMagic(magic_location, GetRand(1));
				break;
			}
		}
	}

	if (attack_time < 0)
	{
		for (int i = 0; i < magic_volume; i++)
		{
			delete magic;
		}
		delete[] magic;

		magic = nullptr;

		attack_state = LAST_BOSS_ATTACK::NONE;
		magic_interval = MAGIC_INTERVAL;
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
		case LAST_BOSS_ATTACK::SPECIAL_MOVES:
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
		damage = bullet->GetDamage() * RESISTANCE_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::RESISTANCE;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::POISON:
	case ATTRIBUTE::PARALYSIS:
	case ATTRIBUTE::HEAL:
	default:
		break;
	}

	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
	hp -= damage;
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


	DrawHPBar(LAST_BOSS_HP);
	DrawDamageLog();

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
//HP�o�[�̕`��
//-----------------------------------
void LastBoss::DrawHPBar(const int max_hp) const
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

	DrawBox(160, 10,SCREEN_WIDTH - 160, 40, 0x000000, TRUE);
	DrawBox(160, 10,160 + (960 * (static_cast<float>(hp) / max_hp)), 40, color, TRUE);
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x8f917f, FALSE);
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