#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlime.h"

#define SLIME_ATTACK_DISTANCE_Y 15
#define SLIME_ATTACK_SPEED 5

//�ړ����x
#define SLIME_SPEED 2
#define SLIME_ATTACK_DAMAGE 10

EnemySlime::EnemySlime()
{
	kind = ENEMY_KIND::SLIME;

	location.x = 1100;
	location.y = 400;


	area.height = 40;
	area.width = 40;

	hp = 100;
	speed = SLIME_SPEED;

	color = GetColor(0, 0, 255);

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	state = ENEMY_STATE::MOVE;
	slime_attack = SLIME_ATTACK::BEFORE_ATTACK;
	direction = DIRECTION::LEFT;
	slime_image = LoadGraph("Images/Enemy/Slime_.png");
	slime_angle = 0;
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
		break;
	case ENEMY_STATE::DEATH:
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
//�A�C�h�����
//-----------------------------------
void EnemySlime::Idol()
{

}

//-----------------------------------
//�ړ�
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

	float distance; //����Ă��鋗��

	//�v���C���[�Ƃ̋����̌v�Z
	distance = sqrtf(powf(player_location.x - location.x, 2) + powf(player_location.y - location.y, 2));

	if (distance < 120)
	{
		state = ENEMY_STATE::ATTACK;
		jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
	}
}


//-----------------------------------
//�U��
//-----------------------------------
AttackResource EnemySlime::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;

	switch (slime_attack)
	{
	case SLIME_ATTACK::BEFORE_ATTACK:
		if(direction == DIRECTION::RIGHT)speed = SLIME_ATTACK_SPEED;
		else speed = -SLIME_ATTACK_SPEED;

		if (HitBox(collider))
		{
			slime_attack = SLIME_ATTACK::AFTER_ATTACK;
			ENEMY_TYPE attack_type[1] = { *type };
			ret.damage = SLIME_ATTACK_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
			jump_distance.y = 0;
		}
		break;

	case SLIME_ATTACK::AFTER_ATTACK:
		if (direction == DIRECTION::RIGHT)speed = -SLIME_ATTACK_SPEED;
		else speed = SLIME_ATTACK_SPEED;

		break;
	}

	location.x += speed;

	if (location.y >= 450)
	{
		slime_attack = SLIME_ATTACK::BEFORE_ATTACK;
		state = ENEMY_STATE::MOVE;
		if (direction == DIRECTION::RIGHT)speed = SLIME_SPEED;
		else speed = -SLIME_SPEED;

	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void EnemySlime::Death()
{
	if (location.y <= 450)
	{
		location.y -= (jump_distance.y / 3);
		jump_distance.y -= 1;
	}
	if (direction == DIRECTION::RIGHT)
	{
		speed = -SLIME_ATTACK_SPEED;
		slime_angle += 15;
	}
	else
	{
		speed = SLIME_ATTACK_SPEED;
		slime_angle -= 15;
	}
	location.x += speed;
	
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


//-----------------------------------
// �v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
bool EnemySlime::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //�߂�l
	if (HitSphere(bullet))
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
		ret = true;
	}
	return ret;
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location EnemySlime::GetLocation() const
{
	return location;
}

