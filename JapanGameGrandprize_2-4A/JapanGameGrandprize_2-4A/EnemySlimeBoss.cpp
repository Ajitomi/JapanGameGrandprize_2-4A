#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlimeBoss.h"
#include"Player.h"
#include"Stage/Stage.h"

#include"BulletManager.h"

#define SLIME_MIN_DROP 0u
#define SLIME_MAX_DROP 3u

#define SLIME_BOSS_SPEED 3
#define SLIME_BOSS_JUMP_SPEED 5
#define SLIME_BOSS_ATTACK_DAMAGE 5
#define SLIME_BOSS_JUMP_DISTANCE 40

#define BOSS_SLIME_HP 500

#define SLIME_BOSS_WAIT_TIME 60

#define SLIME_BOSS_BREATH_TIME 120

#define SLIME_BOSS_WIDTH 180
#define SLIME_BOSS_HEIGHT 200

EnemySlimeBoss::EnemySlimeBoss(Location spawn_location)
{
	location = spawn_location;
	location.y -= 100;

	area.height = SLIME_BOSS_WIDTH;
	area.width = SLIME_BOSS_HEIGHT;

	state = ENEMY_STATE::FALL;
	now_state = state;

	left_move = true;

	kind = ENEMY_KIND::SLIME_BOSS;

	slime_boss_jump_distance = SLIME_BOSS_JUMP_DISTANCE;

	hp = 500;
	speed_y = 0;
	speed = 0;

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	//�h���b�v�A�C�e���̐ݒ�

	int slime_min_drop = 5;
	int slime_drop = 10;

	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < WATER_DROP; i++)
	{
		volume = slime_min_drop + GetRand(slime_drop);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	wait_time = 0;
	breath_time = 0;

	slime_boss_image = LoadGraph("Images/Enemy/SlimeBoss3.png");
}

EnemySlimeBoss::~EnemySlimeBoss()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

}

void EnemySlimeBoss::MagicBullet(const Location player_location)
{
	if (++breath_time >= SLIME_BOSS_BREATH_TIME)
	{
		breath_time = 0;

		BulletManager::GetInstance()->CreateEnemyBullet
		(new SlimeBossBullet(location, player_location));
	}
}


void EnemySlimeBoss::Update(const Player* player, const Stage* stage)
{
	state = now_state;

	Location old_location = location;	//�O�̍��W
	HitMapChip hit_stage = { false,nullptr }; //�X�e�[�W�Ƃ̓����蔻��

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;

	case ENEMY_STATE::MOVE:

		if (left_move)speed = -SLIME_BOSS_SPEED;
		else speed = SLIME_BOSS_SPEED;

		if (--wait_time <= 0)
		{

			speed_y = -(slime_boss_jump_distance / 3);
			if (--slime_boss_jump_distance <= 0)
			{
				state = ENEMY_STATE::FALL;
				speed_y = 0;
				slime_boss_jump_distance = SLIME_BOSS_JUMP_DISTANCE;
			}

			location.y += speed_y;

			hit_stage = HitStage(stage);

			if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
			{
				Location chip_location = hit_stage.chip->GetLocation();
				Area chip_area = hit_stage.chip->GetArea();

				STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
				hit_direction = HitDirection(hit_stage.chip);

				location.y = old_location.y;
			}

			Move(player->GetLocation());

			hit_stage = HitStage(stage);

			if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
			{
				STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
				hit_direction = HitDirection(hit_stage.chip);

				location.x = old_location.x;
				left_move = !left_move;

			}
		}
		else
		{
			MagicBullet(player->GetLocation());
		}

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
			slime_boss_jump_distance = 0;
		}
		break;

	case ENEMY_STATE::FALL:

		if (speed != 0)
		{
			if (left_move)speed = -SLIME_BOSS_SPEED;
			else speed = SLIME_BOSS_SPEED;
		}

		location.x += speed;
		
		hit_stage = HitStage(stage);

		if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
		{
			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			location.x = old_location.x;
			left_move = !left_move;	
		}

		Fall();

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
		{
			Location chip_location = hit_stage.chip->GetLocation();
			Area chip_area = hit_stage.chip->GetArea();

			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			location.y = old_location.y;

			state = ENEMY_STATE::MOVE;

			wait_time = SLIME_BOSS_WAIT_TIME;

		}
		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
			slime_boss_jump_distance = 0;
		}

		break;

	case ENEMY_STATE::ATTACK:

		break;

	case ENEMY_STATE::DEATH:
		Death();
		break;

	default:
		break;
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}

	now_state = state;
	state = ENEMY_STATE::ATTACK;
}

void EnemySlimeBoss::Draw()const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(BOSS_SLIME_HP);
	}
	DrawDamageLog();

	//DrawCircle(draw_location.x, draw_location.y, (area.height / 2), 0xff0000, true, true);
	DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, slime_boss_image, true, !left_move);

	//DrawFormatString(0, 0, 0xffffff, "%d", slime_boss_jump_distance);

}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void EnemySlimeBoss::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -SLIME_BOSS_SPEED;
		}
		else
		{
			speed = SLIME_BOSS_SPEED;
		}
		if (paralysis)
		{
			speed *= PARALYSIS_SPEED;
		}
	}
}

//-----------------------------------
//�ړ�
//-----------------------------------
void EnemySlimeBoss::Move(const Location player_location)
{
	location.x += speed;
}

//-----------------------------------
//����
//-----------------------------------
void EnemySlimeBoss::Fall()
{
	location.y += speed_y;

	if (speed_y < GRAVITY)
	{
		speed_y += ENEMY_FALL_SPEED;
	}
}

//-----------------------------------
//�U��
//-----------------------------------
void  EnemySlimeBoss::Attack(Location player_location)
{
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource EnemySlimeBoss::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	ENEMY_TYPE attack_type[1] = { *type };
	ret.damage = 10;
	ret.type = attack_type;
	ret.type_count = 1;

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void EnemySlimeBoss::Death()
{
	can_delete = true;
}

//-----------------------------------
// �v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void EnemySlimeBoss::HitBullet(const BulletBase* bullet)
{
	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
		break;
	case ATTRIBUTE::EXPLOSION:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
		break;
	case ATTRIBUTE::MELT:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
		break;
	case ATTRIBUTE::POISON:
		//poison_damage = bullet->GetDamage();
		//poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		break;
	case ATTRIBUTE::PARALYSIS:
		paralysis_time = bullet->GetDebuffTime() * 0;
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
Location EnemySlimeBoss::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void EnemySlimeBoss::Update(const ENEMY_STATE state)
{
	if ((old_state != state))
	{
		location = debug_location;
	}


	old_state = state;
}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void EnemySlimeBoss::DebugDraw()
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, 15, 0xff0000, true, true);
}
#endif //_DEBUG

//#ifdef _DEBUG
////-----------------------------------
//// �X�V(DotByDot)
////-----------------------------------
//void EnemySlime::Update(const ENEMY_STATE state)
//{
//	if ((old_state != state) || (attack_time < 0))
//	{
//		location = debug_location;
//	}
//	switch (state)
//	{
//	case ENEMY_STATE::IDOL:
//		break;
//	case ENEMY_STATE::MOVE:
//		if (++image_change_time > 2)
//		{
//			image_type += image_addition;
//			if (image_type == 6)
//			{
//				image_addition = -1;
//			}
//			else if (image_type == 0)
//			{
//				image_addition = 1;
//			}
//			image_change_time = 0;
//		}
//		break;
//	case ENEMY_STATE::FALL:
//		break;
//	case ENEMY_STATE::ATTACK:
//		if ((old_state != state) || (attack_time < 0))
//		{
//			jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
//			attack_time = SLIME_ATTACK_DISTANCE_Y * 3;
//			location = debug_location;
//		}
//		if (SLIME_ATTACK_DISTANCE_Y < attack_time)
//		{
//			location.y -= (jump_distance.y / 3);
//			jump_distance.y--;
//			if (left_move)
//			{
//				speed = -SLIME_ATTACK_SPEED;
//			}
//			else
//			{
//				speed = SLIME_ATTACK_SPEED;
//			}
//			location.x += speed;
//
//		}
//		attack_time--;
//
//		break;
//	case ENEMY_STATE::DEATH:
//		break;
//	default:
//		break;
//	}
//	old_state = state;
//}
//
////-----------------------------------
////�`��(DotByDot)
////-----------------------------------
//void EnemySlime::DebugDraw()
//{
//	DrawRotaGraphF(location.x, location.y, 0.23,
//		M_PI / 180 * slime_angle, images[image_type], TRUE, !left_move);
//
//	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
//		location.x + area.width / 2, location.y + area.height / 2,
//		0xff0000, FALSE);
//}
//#endif //_DEBUG