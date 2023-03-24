#include "EnemySlime.h"
#include "dxlib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "Stage/Stage.h"

#define SLIME_ATTACK_DISTANCE_Y 15
#define SLIME_ATTACK_SPEED 5

//移動速度
#define SLIME_SPEED 2
#define SLIME_ATTACK_DAMAGE 10

#define SLIME_MIN_DROP 1
#define SLIME_DROP 5

#define GROUND 1200
#define WAIT_TIME 30 //プレイヤーを見つけて攻撃するまでの時間

#define ONE_ROUND 360 //一周の角度
#define ROTATION_SPEED 15 //スライムが回転するスピード


EnemySlime::EnemySlime(Location spawn_location)
{
	attack = false;
	left_move = true;
	kind = ENEMY_KIND::SLIME;

	location = spawn_location;

	jump_distance = location;
	area.height = 50;
	area.width = 50;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	wait_time = 0;
	image_type = 0;
	image_change_time = 0;
	image_addition = 1;
	hp = 15;
	speed = SLIME_SPEED;

	slime_attack = SLIME_ATTACK::BEFORE_ATTACK;

	type = new ENEMY_TYPE[1];

	type[0] = static_cast<ENEMY_TYPE>(1 + GetRand(3));

	state = ENEMY_STATE::IDOL;
	images = new int[7];
	 LoadDivGraph("Images/Enemy/mov_slime1.png", 7, 7, 1, 450,269, images);
	slime_angle = 0;

	//ドロップアイテムの設定
	switch (type[0])
	{
	case ENEMY_TYPE::FIRE:
		drop_element = new ElementItem * [FIRE_DROP];
		drop_type_volume = FIRE_DROP;
		break;
	case ENEMY_TYPE::WATER:
		drop_element = new ElementItem * [WATER_DROP];
		drop_type_volume = WATER_DROP;
		break;
	case ENEMY_TYPE::WIND:
		drop_element = new ElementItem * [WIND_DROP];
		drop_type_volume = WIND_DROP;
		break;
	case ENEMY_TYPE::SOIL:
		drop_element = new ElementItem * [SOIL_DROP];
		drop_type_volume = SOIL_DROP;
		break;
	case ENEMY_TYPE::NORMAL:
	case ENEMY_TYPE::THUNDER:
	default:
		break;
	}

	int volume = 0;

	for (int i = 0; i < drop_type_volume; i++)
	{
		volume = SLIME_MIN_DROP + GetRand(SLIME_DROP);

		switch (type[0])
		{
		case ENEMY_TYPE::NORMAL:
			break;
		case ENEMY_TYPE::FIRE:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			break;
		case ENEMY_TYPE::WATER:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			}
			break;
		case ENEMY_TYPE::WIND:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			break;
		case ENEMY_TYPE::SOIL:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			break;
		case ENEMY_TYPE::THUNDER:
			break;
		default:
			break;
		}

		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}


}

EnemySlime::~EnemySlime()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;

}

void EnemySlime::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//前の座標
	HitMapChip hit_stage = { false,nullptr }; //ステージとの当たり判定

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;

	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		hit_stage = HitStage(stage);
		if (hit_stage.hit) //ステージとの当たり判定
		{
			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
			hit_direction = HitDirection(hit_stage.chip);

			if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
			{
				location = old_location;
				left_move = !left_move;
				speed = -speed;
			}
		}
		else
		{
			state = ENEMY_STATE::FALL;
			speed = 0;
		}

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
		}
		break;

	case ENEMY_STATE::FALL:
		Fall();

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //ステージとの当たり判定
		{
			Location chip_location = hit_stage.chip->GetLocation();
			Area chip_area = hit_stage.chip->GetArea();

			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
			hit_direction = HitDirection(hit_stage.chip);

			if (hit_direction == STAGE_DIRECTION::TOP)
			{
				location.y = chip_location.y - 
					(chip_area.height / 2)- (area.height / 2);
				state = ENEMY_STATE::MOVE;
				if (left_move)
				{
					speed = -SLIME_SPEED;
				}
				else
				{
					speed = SLIME_SPEED;
				}
			}
		}

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
		}
		break;

	case ENEMY_STATE::ATTACK:

		Attack(player->GetLocation());

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //ステージとの当たり判定
		{
			location = old_location;
			attack = false;
			state = ENEMY_STATE::MOVE;
			if (left_move)
			{
				speed = -SLIME_SPEED;
			}
			else
			{
				speed = SLIME_SPEED;
			}
		}
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
		jump_distance.y = 15;
	}
}

void EnemySlime::Draw()const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, 0.23, M_PI / 180 * slime_angle, images[image_type], TRUE, !left_move);
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void EnemySlime::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -SLIME_SPEED;
		}
		else
		{
			speed = SLIME_SPEED;
		}
	}
}

//-----------------------------------
//移動
//-----------------------------------
void EnemySlime::Move(const Location player_location)
{
	float distance; //離れている距離

	//プレイヤーとの距離の計算
	distance = sqrtf(powf(player_location.x - location.x, 2) + powf(player_location.y - location.y, 2));

	if (distance < 120 &&
	  ((left_move && player_location.x <= location.x) ||
	  (!left_move && player_location.x >= location.x)))
	{
		if (++wait_time >= WAIT_TIME)
		{
			state = ENEMY_STATE::ATTACK;
			jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
			wait_time = 0;
		}
	}
	else
	{
		if (++image_change_time > 2)
		{
			image_type += image_addition;
			if (image_type == 6)image_addition = -1;
			else if(image_type == 0) image_addition = 1;
			image_change_time = 0;
		}


		location.x += speed;
		wait_time = 0;
	}

	
}

//-----------------------------------
//落下
//-----------------------------------
void EnemySlime::Fall()
{
	location.y += speed;
	if (speed < GRAVITY)
	{
		speed += ENEMY_FALL_SPEED;
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void  EnemySlime::Attack(Location player_location)
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;

	if (left_move) speed = -SLIME_ATTACK_SPEED;
	else speed = SLIME_ATTACK_SPEED;

	location.x += speed;
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource EnemySlime::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (!attack)
	{
		attack = true;
		slime_attack = SLIME_ATTACK::AFTER_ATTACK;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = SLIME_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void EnemySlime::Death()
{
	can_delete = true;

	/*if (slime_angle >= (ONE_ROUND * 2.5) || slime_angle <= -(ONE_ROUND * 2.5))
	{
		can_delete = true;
	}
	else
	{
		if (location.y <= GROUND)
		{
			location.y -= (jump_distance.y / 3);
			jump_distance.y--;
		}
		if (left_move)
		{
			speed = SLIME_ATTACK_SPEED;
			slime_angle += ROTATION_SPEED;
		}
		else
		{
			speed = -SLIME_ATTACK_SPEED;
			slime_angle -= ROTATION_SPEED;
		}
		location.x += speed;
	}*/
}

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
void EnemySlime::HitBullet(const BulletBase* bullet)
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
//座標の取得
//-----------------------------------
Location EnemySlime::GetLocation() const
{
	return location;
}