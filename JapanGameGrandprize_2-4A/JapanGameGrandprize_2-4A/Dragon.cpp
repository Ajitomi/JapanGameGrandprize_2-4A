#include "Dragon.h"
#include "CameraWork.h"
#include"BulletManager.h"
#include "DxLib.h"

//�h���S���̉摜�T�C�Y(����A�摜���o�����撲���j
#define DRAGON_SIZE_X 250
#define DRAGON_SIZE_Y 250

//�h���S����HP
#define HIT_POINTS 500

//�h���S���̈ړ����x
#define ATTACK_SPEED 3
#define SPEED 10

//�h���S���K���U��
#define ATTACK_SCOPE 100
#define ATTACK_SCOPE_Y 10

//���@�U���������̍d������
#define MAGIC_STANDBY 60

//�ߐڍU���������̍d������
#define PHYSICAL_STANDBY 100

//���K��̍d������
#define	ROAR_TIME 130

//���̐�
#define THUNDER 4

//�h���S���̍U����(�U���ʁj
//�K���U��
#define ATTACK_TAIL 20

//���݂�
#define ATTACK_DITE 30 

//�ڋߍU���͈̔�
#define MELEE_ATTACK 150

//�U���؂�ւ�����
#define ATTACK_SWITCHOVER 10

//�u���X���ˊԊu
#define BREATH_INTERVAL 120

//�h���b�v��(�ŏ�)
#define MIN_DROP 40

//�h���b�v��(�ő�)
#define MAX_DROP 60

Dragon::Dragon(Location spawn_location)
{
	location = spawn_location;
	location.y = 500;
	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	area.height = DRAGON_SIZE_Y;
	area.width = DRAGON_SIZE_X;

	hp = HIT_POINTS;
	speed = SPEED;

	animation = 0;
	attack_method = 0;
	magic_num = 0;
	old_x = 0;
	old_y = 0;
	player_x = 0;
	player_y = 0;
	animation_time = 0;
	switchover_time = 0;
	effect_time = 0;
	standby_time = 0;
	breath_time = 0;
	ascent_time = 0;
	fly_tim = 0;
	fly_num = 0;

	can_delete = false;
	attack_tail = false;
	wall_hit = false;
	left_move = true;
	attack = false;
	magic = false;

	kind = ENEMY_KIND::DRAGON;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::FIRE;

	state = ENEMY_STATE::IDOL;

	attack_state = DRAGON_ATTACK::NONE;

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [FIRE_DROP];
	drop_type_volume = FIRE_DROP;

	int volume = 0;
	for (int i = 0; i < FIRE_DROP; i++)
	{
		volume = MIN_DROP + GetRand(MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	image = LoadGraph("Images/Enemy/a.png"); //�摜�Ǎ���

}

Dragon::~Dragon()
{
	delete[] type;

	for (int i = 0; i < FIRE_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

void Dragon::Update(const class Player* player, const class Stage* stage)
{
	Location old_location = location;	//�O�̍��W
	HitMapChip hit_stage = { false,nullptr }; //�X�e�[�W�Ƃ̓����蔻��

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
		hit_stage = HitStage(stage);

		if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
		{
			Location chip_location = hit_stage.chip->GetLocation();
			Area chip_area = hit_stage.chip->GetArea();

			location.y = chip_location.y -
				(chip_area.height / 2) - (area.height / 2);

			STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
			hit_direction = HitDirection(hit_stage.chip);

			if (hit_direction == STAGE_DIRECTION::TOP)
			{
				state = ENEMY_STATE::MOVE;
				speed = SPEED;
				fall_speed = 0;
				fly_num = 0;
				fly_tim = 0;
				ascent_time = 0;

			}
		}
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		wall_hit = false;
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}

	hit_stage = HitStage(stage);

	if (hit_stage.hit) //�X�e�[�W�Ƃ̓����蔻��
	{
		STAGE_DIRECTION hit_direction; //���������X�e�[�W�u���b�N�̖�
		hit_direction = HitDirection(hit_stage.chip);

		if (hit_direction == STAGE_DIRECTION::TOP)
		{
			location = old_location;
		}
		if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
		{
			location = old_location;
			left_move = !left_move;
			wall_hit = true;

			state = ENEMY_STATE::MOVE;
		}

	}

	//��ʓ����W
	Location s_location = { location.x - CameraWork::GetCamera().x,location.y - CameraWork::GetCamera().y };

	//��ʊO(��)�ɏo�����̔���
	bool is_out_screen = s_location.x - area.width / 2 < 0 || SCREEN_WIDTH < s_location.x + area.width / 2;

	if (is_out_screen == true)
	{
		location = old_location;
		left_move = !left_move;
		wall_hit = true;

		state = ENEMY_STATE::MOVE;
	}

	//��ʏ㕔����o���猳�̈ʒu�ɖ߂�
	if (s_location.y - area.height / 2 < 0)
	{
		location = old_location;
	}


	//�ł̃_���[�W
	if (poison == true)
	{
		if (++effect_time % POISON_DAMAGE_FLAME == 0)
		{
			if (--poison_time > 0)
			{
				hp -= poison_damage;
			}
			else
			{
				poison_damage = 0;
				poison_time = 0;
				poison = false;
			}

		}
	}


	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}

}

//-----------------------------------
//�`��
//-----------------------------------
void Dragon::Draw() const
{
	//�X�N���[���ɍ��킹�ĕ`��
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2,
		GetColor(255, 0, 0), TRUE);

	/*DrawRotaGraphF(draw_location.x, draw_location.y, 1.4f,
		M_PI / 180, image, TRUE);*/

	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(HIT_POINTS);
	}
	DrawDamageLog();

}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Dragon::Idol()
{
	Location scroll; //��ʃX�N���[�����l������X���W
	Location camera = CameraWork::GetCamera(); //�J����
	scroll = location - camera;

	if ((-area.width < scroll.x) && (scroll.x < SCREEN_WIDTH + area.width) &&
		(-area.height < scroll.y) && (scroll.y < SCREEN_HEIGHT + area.height))
	{
		state = ENEMY_STATE::FALL;
	}
}

//-----------------------------------
//����
//-----------------------------------
void Dragon::Move(const Location player_location)
{


	//�v���C���[�Ƃ̋����v�Z
	int range = player_location.x - location.x;
	int range_y = player_location.y - location.y;

	if (range <= ATTACK_SCOPE && range >= -ATTACK_SCOPE &&
		range_y <= ATTACK_SCOPE_Y && range_y >= -ATTACK_SCOPE_Y)
	{
		attack_state = DRAGON_ATTACK::TAIL_ATTACK;
		state = ENEMY_STATE::ATTACK;
	}

	standby_time--;
	if (standby_time < 0)
	{

		switch (attack_method)
		{
		case 0:
			attack_state = DRAGON_ATTACK::DITE;
			state = ENEMY_STATE::ATTACK;
			break;
		case 1:
			attack_state = DRAGON_ATTACK::DREATH;
			state = ENEMY_STATE::ATTACK;
			magic = true;
			break;
		case 2:
			attack_state = DRAGON_ATTACK::ROAR;
			state = ENEMY_STATE::ATTACK;
			magic = true;
			break;
		default:
			break;
		}
	}
}

//-----------------------------------
//�U��
//-----------------------------------
void Dragon::Attack(const Location player_location)
{


	switch (attack_state)
	{

	case DRAGON_ATTACK::DITE://���݂�
		DiteMove(player_location);
		break;
	case DRAGON_ATTACK::TAIL_ATTACK: //�K���U��
		attack = false;
		state = ENEMY_STATE::MOVE;
		break;
	case DRAGON_ATTACK::DREATH: //�u���X�U��
		DreathMove(player_location);
		break;
	case DRAGON_ATTACK::ROAR: //���K������ɗ����~�点��
		RoarMove(player_location);
		break;
	case DRAGON_ATTACK::NONE:
	default:
		break;
	}
	

}

//-----------------------------------
//�ڋߍU�����̊��݂�(�������΂�Ȃ���U���j�̓����肷��C���[�W
//-----------------------------------
void Dragon::DiteMove(const Location player_location)
{
	//4��7�����݁A�ǂɓ�����܂ōU���𑱂���̂��A��4��10�����݂���i�X�e�[�W�Ƃ̌��ˍ��������邽�߉�����j
	//�U���J�n����̃v���C���[�̍��W��ڎw���Ĉړ�����̂��A

	speed = ATTACK_SPEED;

	if (left_move == true)
	{
		location.x -= speed;
		speed = SPEED;
	}
	else
	{
		location.x += speed;
		speed = SPEED;
	}

	if (wall_hit == true)
	{
		attack_method = GetRand(2);

		state = ENEMY_STATE::MOVE;
	}

}


//-----------------------------------
//�������U���i�u���X�j���̎���тȂ���u���X���s��
//-----------------------------------
void Dragon::DreathMove(const Location player_location)
{
	Fly();
	if (++breath_time % BREATH_INTERVAL == 0)
	{
		BulletManager::GetInstance()->CreateEnemyBullet
		(new DragonBullet(location, player_location));
	}
}

//-----------------------------------
//�������U���i���K�j
//-----------------------------------
void Dragon::RoarMove(const Location player_location)
{

	//for (int i = 0; i < THUNDER; i++)
	//{
	//  GetRand(???)���g���āA�����_���ȍ��W�ɗ��𗎂Ƃ�����
	// 	//�X�e�[�W�Ƃ̌��ˍ��������邽�߁A���݂̓R�����g�A�E�g
	// 
	//	BulletManager::GetInstance()->CreateEnemyBullet
	//	(new DragonThunder(player_location.x, player_location.y-60)); 
	//}




	attack_method = GetRand(2);


	standby_time = ROAR_TIME;

	state = ENEMY_STATE::MOVE;

	standby_time = 200;

}

//-----------------------------------
//�U�������������̂�
//-----------------------------------
AttackResource Dragon::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	if (attack_state == DRAGON_ATTACK::DITE)
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = ATTACK_DITE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	if (attack_state == DRAGON_ATTACK::TAIL_ATTACK && (!attack))
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = ATTACK_TAIL;
		ret.type = attack_type;
		ret.type_count = 2;
	}

	return ret;
}

//-----------------------------------
//����
//-----------------------------------
void Dragon::Fall()
{
	location.y += fall_speed;

	if (fall_speed < 4)
	{
		fall_speed += ENEMY_FALL_SPEED;
	}

}

//-----------------------------------
//���
//-----------------------------------
void Dragon::Fly()
{
	if (++ascent_time < 120)
	{
		location.y -= 4;
	}

	if (++fly_tim % 120 == 0)
	{
		if (++fly_num > 4)
		{
			state = ENEMY_STATE::FALL;
			attack_method = GetRand(2);
			standby_time = 200;
		}
	}
	if (fly_num < 4)
	{
		speed = ATTACK_SPEED;

		if (left_move == true)
		{
			location.x -= speed;
			speed = SPEED;
		}
		else
		{
			location.x += speed;
			speed = SPEED;
		}
	}
}

//-----------------------------------
//���S�i�|���ꂽ�j
//-----------------------------------
void Dragon::Death()
{
	can_delete = true;
}

//-----------------------------------
//�v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void Dragon::HitBullet(const BulletBase* bullet)
{

	int i = 0;
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

	switch (bullet->GetAttribute()) //�󂯂��������̑���
	{
	case ATTRIBUTE::NORMAL: //�ʏ�e 
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE; //�����ɂ���
		break;
	case ATTRIBUTE::EXPLOSION: //���� 
		hp -= bullet->GetDamage() * 0; //�����Ȃ�
		break;
	case ATTRIBUTE::MELT: //�n���� �@�ʏ�
		hp -= bullet->GetDamage(); //�ʏ�_���[�W
		break;
	case ATTRIBUTE::POISON: //�Ł@
		if (!poison)
		{
			poison = true;
			poison_time = bullet->GetDebuffTime();
			poison_damage = bullet->GetDamage();
		}
		break;
	case ATTRIBUTE::PARALYSIS: //��� ��_
		if (!paralysis)
		{
			paralysis = true;
			paralysis_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;  //��_
		}
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}
	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Dragon::GetLocation() const
{
	return Location();
}


#ifdef _DEBUG
//-----------------------------------
// �X�V(DotByDot)
//-----------------------------------
void Dragon::Update(const ENEMY_STATE state)
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
}

//-----------------------------------
//�`��(DotByDot)
//-----------------------------------
void Dragon::DebugDraw()
{

}
#endif //_DEBUG