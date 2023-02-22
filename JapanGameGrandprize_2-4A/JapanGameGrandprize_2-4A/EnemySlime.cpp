#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlime.h"

#define SLIME_ATTACK_DISTANCE_Y 15
#define SLIME_ATTACK_SPEED 5

//移動速度
#define SLIME_SPEED 2
#define SLIME_ATTACK_DAMAGE 10

EnemySlime::EnemySlime()
{
	kind = ENEMY_KIND::SLIME;

	location.x = 1100;
	location.y = 450;


	area.height = 40;
	area.width = 40;

	hp = 5;
	speed = SLIME_SPEED;

	color = GetColor(0, 0, 255);

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	state = ENEMY_STATE::MOVE;
	direction = DIRECTION::LEFT;
	slime_image = LoadGraph("Images/Enemy/Slime_.png");
	slime_angle = 0;
}

EnemySlime::EnemySlime(float x, float y, float height, float width)
{
	location.x = x;
	location.y = y;
	area.height = height;
	area.width = width;
}

void EnemySlime::Update()
{
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;

	case ENEMY_STATE::MOVE:
		break;

	case ENEMY_STATE::ATTACK:
		Attack();
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}

void EnemySlime::Draw()const
{
	/*DrawCircle(location.x - CameraWork::GetCamera().x , location.y, 20, color, 1, 1);
	DrawCircle(location.x - CameraWork::GetCamera().x, location.y + 8, 7, 0x000000, 1, 1);
	DrawCircle(location.x - 7 - CameraWork::GetCamera().x, location.y - 6, 4, 0xffffff, 1, 1);
	DrawCircle(location.x + 7 - CameraWork::GetCamera().x, location.y - 6, 4, 0xffffff, 1, 1);
	DrawCircle(location.x - 7 + (1 * direction) - CameraWork::GetCamera().x, location.y - 6, 2, 0x000000, 1, 1);
	DrawCircle(location.x + 7 + (1 * direction) - CameraWork::GetCamera().x, location.y - 6, 2, 0x000000, 1, 1);
	DrawBox(location.x - (area.width / 2)-CameraWork::GetCamera().x, location.y - (area.height / 2), location.x - (area.width / 2) + area.width- CameraWork::GetCamera().x, location.y - (area.height / 2) + area.height, 0xffffff, 0);*/

	DrawRotaGraph(location.x - CameraWork::GetCamera().x, location.y, 0.17, M_PI / 180 * slime_angle, slime_image, TRUE);
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void EnemySlime::Idol()
{

}

//-----------------------------------
//移動
//-----------------------------------
void EnemySlime::Move(const Location player_location)
{

	if (location.x >= 1260)
	{
		direction = DIRECTION::LEFT;
		speed  = -SLIME_SPEED;
	}
	if (location.x <= 20)
	{
		direction = DIRECTION::RIGHT;
		speed = SLIME_SPEED;
	}
	location.x += speed;
}


//-----------------------------------
//攻撃
//-----------------------------------
AttackResource EnemySlime::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;
	if (location.x >= 1260)
	{
		speed = -SLIME_ATTACK_SPEED;
	}
	if (location.x <= 20)
	{
		speed = SLIME_ATTACK_SPEED;
	}

	location.x += speed;
	
	if (HitBox(collider))
	{
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = SLIME_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
		jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
		color = GetColor(255, 0, 0);
		KnockBack();
	}
	else
	{
		color = GetColor(0, 0, 255);
	}

	if (location.y >= 490)
	{
		state = ENEMY_STATE::MOVE;
	}
	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void EnemySlime::Death()
{
	if (direction == DIRECTION::LEFT)
	{
		slime_angle += -15;
	}
	else
	{
		slime_angle += 15;
	}
	
	location.x += speed;

	if (slime_angle >= 880 || slime_angle <= -880)
	{
		slime_angle = 180;
		
	}
}

void EnemySlime::HitStage()
{

}

void EnemySlime::KnockBack()
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;
	location.x += -speed;
	
	if (location.y >= 490)
	{
		state = ENEMY_STATE::MOVE;
	}
}

