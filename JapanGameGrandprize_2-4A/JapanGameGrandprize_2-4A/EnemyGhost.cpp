#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//�v���C���[��������
#define GHOST_DETECTION_DISTANCE 500

//�����U���͈�
#define GHOST_ATTACK_RANGE 20

//���@�U���͈�	
#define GHOST_ATTACK_MAGIC 400

//���@�U���������̍d������
#define GHOST_MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define GHOST_PHYSICAL_STANDBY 300

//�ړ��X�s�[�h
#define GHOST_SPEED 1.5

//�U���X�s�[�h
#define ATTACK_SPEED 4.5

//�h���b�v��(�ŏ�)
#define GHOST_MIN_DROP 0u

//�h���b�v��(�ő�)
#define GHOST_MAX_DROP 4u

//�S�[�X�g�̍U����
#define GHOST_ATTACK_DAMAGE 10

//������邱��
//�����蔻��A�ڋߍU������ł����̂�

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	can_delete = false;
	hp = 10;
	location.x = 600;
	location.y = 1200;
	area.width = GHOST_SIZE_X;
	area.height = GHOST_SIZE_Y;
	standby_time = 0;
	standby_count = 0;
	physical_attack = false;
	magic_attack = false;
	kind = ENEMY_KIND::GHOST;

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;
	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = GHOST_MIN_DROP + GetRand(GHOST_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = GHOST_STATE::NORMAL;
	bullet = nullptr;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
EnemyGhost::~EnemyGhost()
{
	delete bullet;
}

//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
{
	float screen_x; //��ʃX�N���[�����l������X���W

	screen_x = location.x - CameraWork::GetCamera().x;

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		if ((-area.width < screen_x) && (screen_x < SCREEN_WIDTH + area.width))
		{
			state = ENEMY_STATE::MOVE;
		}
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

	if (bullet != nullptr)
	{
		bullet->Update();

		if (bullet->ScreenOut())
		{
			delete bullet;
			bullet = nullptr;
			attack_state = GHOST_ATTACK::NONE;
		}
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}

}

//�A�C�h�����
void EnemyGhost::Idol()
{

}

//�ړ�
void EnemyGhost::Move(const Location player_location)
{
	GhostMove(player_location);

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //�ʏ�ړ�
		location.x -= GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_lOWER:  //������ڎw��
		location.x -= GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_UPPER:  //�����ڎw��
		location.x -= GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //�E����ڎw��
		location.x += GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //�E���ڎw���B
		location.x += GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	default:
		break;
	}
}

//-----------------------------------
//�U��
//-----------------------------------
void  EnemyGhost::Attack(Location player_location)
{
	standby_count++;
	if (standby_time < standby_count)
	{
		switch (attack_state)
		{
		case GHOST_ATTACK::PHYSICAL_ATTACK:
			physical_attack = false;
			attack_state = GHOST_ATTACK::NONE;
			break;
		case GHOST_ATTACK::MAGIC_ATTACK:
			magic_attack = false;
			break;
		case GHOST_ATTACK::NONE:
			break;
		default:
			break;
		}
		standby_time = 0;
		standby_count = 0;
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource EnemyGhost::HitCheck(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	switch (attack_state)
	{
	case GHOST_ATTACK::PHYSICAL_ATTACK:
		if (HitBox(collider))
		{
			ENEMY_TYPE attack_type[1] = { *type };
			ret.damage = GHOST_ATTACK_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		if (bullet != nullptr)
		{
			if (bullet->HitBox(collider))
			{
				ENEMY_TYPE attack_type[1] = { bullet->GetType() };
				ret.damage = bullet->GetDamage();
				ret.type = attack_type;
				ret.type_count = 1;

				delete bullet;
				bullet = nullptr;
			}
		}
		break;
	case GHOST_ATTACK::NONE:
		break;
	default:
		break;
	}

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void EnemyGhost::Death()
{
	can_delete = true;
}

//-----------------------------------
// �`��
//-----------------------------------
void EnemyGhost::Draw()const
{
	//�X�N���[���ɍ��킹�ĕ`��
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	switch (attack_state)
	{
	case GHOST_ATTACK::PHYSICAL_ATTACK:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
		if (bullet != nullptr)
		{
			bullet->Draw();
		}
		break;
	case GHOST_ATTACK::NONE:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
		break;
	default:
		break;
	}
}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(const Location player_location)
{
	float range; //�v���C���[�Ƃ̋���	
	
	range = fabsf(location.x - player_location.x);

	//�v���C���[�������������ɂ�����
	if (range <= GHOST_DETECTION_DISTANCE && range >= -GHOST_DETECTION_DISTANCE)
	{
		if (range > player_location.x) //���Ɉړ�
		{
			if (player_location.y > location.y)
			{
				action_type = GHOST_STATE::LEFT_lOWER;
			}
			else 
			{
				action_type = GHOST_STATE::LEFT_UPPER;
			}
		}
		else //�E�Ɉړ�
		{
			if (player_location.y > location.y)
			{
				action_type = GHOST_STATE::RIGHT_LOWER;
			}
			else
			{
				action_type = GHOST_STATE::RIGHT_UPPER;
			}
		}
	}
	else //�ʏ�ړ�
	{
		action_type = GHOST_STATE::NORMAL;
		magic_attack = false;
		physical_attack = false;
	}

	//�U���͈͓��ɂ���ꍇ
	if ((range <= GHOST_ATTACK_RANGE) && (!physical_attack))
	{
		state = ENEMY_STATE::ATTACK;
		attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
		standby_time = GHOST_PHYSICAL_STANDBY;
		physical_attack = true;
	}
	else if ((range <= GHOST_ATTACK_MAGIC) && (!magic_attack))
	{
		state = ENEMY_STATE::ATTACK;
		attack_state = GHOST_ATTACK::MAGIC_ATTACK;
		standby_time = GHOST_MAGIC_STANDBY;
		magic_attack = true;

		if (bullet == nullptr)
		{
			bullet = new GhostBullet(location, player_location);
		}
	}
}

//-----------------------------------
// �v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
bool EnemyGhost::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //�߂�l
	if (HitSphere(bullet))
	{
		switch (bullet->GetAttribute()) //�󂯂��������̑���
		{
		case ATTRIBUTE::NORMAL: 
			hp -= bullet->GetDamage() * 10; //����
			break;
	//	case ATTRIBUTE::EXPLOSION:
	//		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE; //��_����
	//		break;
	//	case ATTRIBUTE::MELT:
	//		hp -= bullet->GetDamage() * 0; //����
	//		break;
	//	case ATTRIBUTE::POISON:
	//		poison_damage = bullet->GetDamage() * 0; //����
	//		poison_time = bullet->GetDebuffTime() * 0; //����
	//		break;
	//	case ATTRIBUTE::PARALYSIS:
	//		paralysis_time = bullet->GetDebuffTime() * 0; //����
	//		paralysis_time = bullet->GetDamage() * 0; //����
	//		break;
	//	case ATTRIBUTE::HEAL:
	//		break;
	//	default:
	//		break;
		}
		ret = true;
	}
	return ret;
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location EnemyGhost::GetLocation() const
{
	return location;
}