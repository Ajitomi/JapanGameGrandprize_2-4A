#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//�S�[�X�g�̉摜�T�C�Y
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//�v���C���[��������
#define DETECTION_DISTANCE 500

//�����U���͈�
#define ATTACK_RANGE 15

//���@�U���͈�	
#define ATTACK_MAGIC 400

//�ړ��X�s�[�h
#define GHOST_SPEED 1.5

//�U���X�s�[�h
#define ATTACK_SPEED 4.5

//�h���b�v��(�ŏ�)
#define GHOST_MIN_DROP 0u

//�h���b�v��(�ő�)
#define GHOST_MAX_DROP 4u

//�h���b�v�����ސ�
#define GHOST_DROP 3



//������邱��
//�����蔻��A�A�C�e�������A�ڋߍU������ł����̂�

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	can_delete = false;
	hp = 10;
	location.x = 600;
	location.y = 300;
	area.width = GHOST_SIZE_X;
	area.height = GHOST_SIZE_Y;
	standby_time = 0;
	bullet_x = 0;
	bullet_y = 0;
	player_x = 0;
	player_y = 0;
	bullet_speed_x = 0;
	bullet_speed_y = 0;
	physical_attack = false;
	magic_attack = false;
	setting_bullet = false;
	action_type = GHOST_STATE::NORMAL;
	kind = ENEMY_KIND::GHOST;

	//�h���b�v�A�C�e���̐ݒ�
	drop_element = new ElementItem * [GHOST_DROP];
	drop_type_volume = GHOST_DROP;

	int volume = 0;
	for (int i = 0; i < GHOST_DROP; i++)
	{
		volume = GHOST_MIN_DROP + GetRand(GHOST_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}


}


//-----------------------------------
// �`��ȊO�̏���
//-----------------------------------
void EnemyGhost::Update()
{

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
	case GHOST_STATE::MAGIC_ATTACK: //���@�U��
		if (++standby_time % 300 == 0) //�d������
		{
			magic_attack = true;
			standby_time = 0;
		}
		break;
	case GHOST_STATE::PHYSICAL_ATTACK: //�ڋߍU��
		if (++standby_time % 60 == 0) //�d������
		{
			physical_attack = true;
			standby_time = 0;
		}
		break;
	}

	GhostAttack(); //�U��

	if (CheckHp() == true)
	{
		can_delete = true;
	}

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


	DrawFormatString(100, 100, GetColor(255, 0, 0), "%d", action_type);

	if (action_type == GHOST_STATE::MAGIC_ATTACK) //���@�U���̃��[�V����
	{
		DrawBox(x, y, x + area.width, y + area.height, GetColor(128, 0, 0), TRUE);
	}
	else if (action_type == GHOST_STATE::PHYSICAL_ATTACK) //�ڋߍU���̃��[�V����
	{
		DrawBox(x, y, x + area.width, y + area.height, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		DrawBox(x, y, x + area.width, y + area.height, GetColor(255, 255, 0), TRUE);
	}

	if (magic_attack == true)
	{
		DrawCircle(bullet_x, bullet_y, 5, GetColor(128, 0, 0));
	}
}


//-----------------------------------
// �S�[�X�g�̓���
//-----------------------------------
void EnemyGhost::GhostMove(Player* player)
{
	int range; //�v���C���[�Ƃ̋���	
	
	range = location.x - player->GetLocation().x;

	//�v���C���[�������������ɂ�����
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (location.x > player->GetLocation().x) //���Ɉړ�
		{
			if (player->GetLocation().y > location.y)
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
			if (player->GetLocation().y > location.y)
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
	}

	//�U���͈͓��ɂ���ꍇ
	if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE && physical_attack == false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}
	else if (range <= ATTACK_MAGIC && range >= -ATTACK_MAGIC && magic_attack == false)
	{
		player_x = player->GetLocation().x;
		player_y = player->GetLocation().y;
		action_type = GHOST_STATE::MAGIC_ATTACK;
	}

	if (HitBox(player) != false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}



}



//-----------------------------------
// �S�[�X�g�̍U������
//-----------------------------------
void EnemyGhost::GhostAttack()
{

	if (magic_attack == true) //���@�U��
	{
		if (setting_bullet == false) //�e�ۏ����ݒ�
		{
			bullet_x = location.x;
			bullet_y = location.y;
			setting_bullet = true;
			// �e�̈ړ����x��ݒ肷��
			{
				float sb, sbx, sby, bx, by, sx, sy;

				sx = bullet_x;
				sy = bullet_y;

				bx = player_x;
				by = player_y;

				sbx = bx - sx;
				sby = by - sy;

				sb = sqrt(sbx * sbx + sby * sby);

				// �P�t���[��������2�h�b�g�ړ�����悤�ɂ���
				bullet_speed_x = sbx / sb * 2;
				bullet_speed_y = sby / sb * 2;
			}
		}
		else
		{
			bullet_x += bullet_speed_x;
			bullet_y += bullet_speed_y;
		}

	}

	if (physical_attack == true) //�����U��
	{
		
	}
}

//-----------------------------------
// �v���C���[�̒e�ۂƂ̓����蔻��
//-----------------------------------
void EnemyGhost::HitBullet(BulletBase* bullet)
{

}



