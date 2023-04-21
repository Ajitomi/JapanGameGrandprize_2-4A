#include "LastBossHand.h"
#include "Player.h"
#include "Stage/Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

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

//HP
#define HAND_HP 1000

//���S���Ă��鎞��
#define DEATH_TIME 600

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossHand::LastBossHand(const Location spawn_location, const bool left_hand)
{
	location = spawn_location;
	punch_start = location;

	area.height = 100;
	area.width = 100;

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
	hp = HAND_HP;
	speed = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	drop_volume = 0;
	drop_type_volume = 0;
	drop_element = nullptr;

	kind = ENEMY_KIND::LAST_BOSS;
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

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;

		location.x = -100;
		location.y = -100;
		death_time = DEATH_TIME;
	}

	UpdateDamageLog();
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
	bool old_punch = punch;

	if (punch) //�p���`���Ă���
	{
		Punch();
	}
	else
	{
		location.x = player_location.x;
		punch = true;
	}

	if (old_punch && (old_punch != punch)) //�p���`�I��
	{
		state = ENEMY_STATE::MOVE;
		attack_interval = PUNCH_INTERVAL;
		attack = false;

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
			attack = false;
		}

		if (punch_start.y <= location.y)
		{
			punch = false;
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
	death_time--;

	if (death_time < 0)
	{
		state = ENEMY_STATE::MOVE;

	}
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void LastBossHand::HitBullet(const BulletBase* bullet)
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
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
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
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	if (state != ENEMY_STATE::DEATH)
	{
		draw_location = draw_location - camera;

		DrawHPBar(HAND_HP);

		DrawDamageLog();

		DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
			draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xffffff, TRUE);

	}

}

//-----------------------------------
//HP�o�[�̕\��
//-----------------------------------
void LastBossHand::DrawHPBar(const int)const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();

	int bar_size = 50;

	draw_location = draw_location - camera;

	DrawBox(draw_location.x - bar_size, draw_location.y - 80,
		draw_location.x + bar_size, draw_location.y - 70, 0x000000, TRUE);

	DrawBox(draw_location.x - bar_size, draw_location.y - 80,
		draw_location.x - bar_size + ((bar_size * 2) * (static_cast<float>(hp) / HAND_HP)),
		draw_location.y - 70, 0x07ff00, TRUE);

	DrawBox(draw_location.x - bar_size, draw_location.y - 80,
		draw_location.x + bar_size, draw_location.y - 70, 0x8f917f, FALSE);
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