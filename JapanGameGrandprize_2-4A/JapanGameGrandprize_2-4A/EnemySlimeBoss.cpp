#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlimeBoss.h"
#include"Player.h"
#include"Stage/Stage.h"

#define SLIME_MIN_DROP 0u
#define SLIME_MAX_DROP 3u

#define SLIME_BOSS_SPEED 3
#define SLIME_BOSS_JUMP_SPEED 5
#define SLIME_BOSS_ATTACK_DAMAGE 5
#define SLIME_BOSS_JUMP_DISTANCE 40

#define BOSS_SLIME_HP 500

EnemySlimeBoss::EnemySlimeBoss(Location spawn_location)
{
	location = spawn_location;
	location.y -= 100;

	area.height = 150;
	area.width = 150;

	state = ENEMY_STATE::FALL;

	left_move = false;

	if (left_move)speed = -SLIME_BOSS_SPEED;
	else speed = SLIME_BOSS_SPEED;

	kind = ENEMY_KIND::SLIME_BOSS;

	slime_boss_jump_distance = 0;

	hp = 500;
	speed_y = 0;

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

	move_state = MOVE_STATE::MOVE;
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



void EnemySlimeBoss::Update(const Player* player, const Stage* stage)
{
	if (left_move)speed = -SLIME_BOSS_SPEED;
	else speed = SLIME_BOSS_SPEED;

	Location old_location = location;	//�O�̍��W
	HitMapChip hit_stage = { false,nullptr }; //�X�e�[�W�Ƃ̓����蔻��

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;

	case ENEMY_STATE::MOVE:

		switch (move_state)
		{
		case MOVE_STATE::MOVE:

			speed_y = -(slime_boss_jump_distance / 3);
			if (--slime_boss_jump_distance <= 0)
			{
				state = ENEMY_STATE::FALL;
				speed_y = 0;
				slime_boss_jump_distance = SLIME_BOSS_JUMP_DISTANCE;
			}

			break;

		case MOVE_STATE::WALL_MOVE:

			break;
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
			
			state = ENEMY_STATE::FALL;
			speed_y = 0;
			slime_boss_jump_distance = SLIME_BOSS_JUMP_DISTANCE;
			speed = 0;
		}
		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
			slime_boss_jump_distance = 0;
		}
		break;

	case ENEMY_STATE::FALL:

		location.x += speed;
		
		hit_stage = HitStage(stage);

		if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
		{
			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			location.x = old_location.x;
			left_move = !left_move;
			
			switch (move_state)
			{
			case MOVE_STATE::MOVE:
				
				break;

			case MOVE_STATE::WALL_MOVE:

				break;
			}
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

			switch (move_state)
			{
			case MOVE_STATE::MOVE:
				
				break;

			case MOVE_STATE::WALL_MOVE:

				break;
			}
		}
		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
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

	DrawCircle(draw_location.x, draw_location.y, (area.height / 2), 0xff0000, true, true);

	DrawFormatString(0, 0, 0xffffff, "%d", slime_boss_jump_distance);

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