#include "EnemyBulletBase.h"
#include "Define.h"
#include "CameraWork.h"
#include "Stage/Stage.h"
#include "BULLET.h"

//-----------------------------------
//��ʊO�ɏo�����ǂ���
//-----------------------------------
bool EnemyBulletBase::ScreenOut()
{
	bool ret = false; //�߂�l
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	if ((x < 0) || (SCREEN_WIDTH < x) || (y < 0) || (SCREEN_HEIGHT < y))
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//�X�e�[�W�Ƃ̓����蔻��
//-----------------------------------
bool EnemyBulletBase::HitStage(const Stage* stage) const
{
	bool ret = false; //�߂�l

//�}�b�v�`�b�v
	std::vector<MapChip*>map_chip = stage->GetMapChip();

	//�J�����̈ʒu
	Location camera = CameraWork::GetCamera();

	//�`��͈͂̐ݒ�
	Area draw_area = { SCREEN_HEIGHT + CHIP_SIZE,SCREEN_WIDTH + CHIP_SIZE };

	for (MapChip* chip : map_chip)
	{
		if (chip != nullptr)
		{
			Location draw_location = chip->GetLocation();
			Area draw = chip->GetArea();

			//�`��͈͓��ɂ���u���b�N
			if ((camera.x < draw_location.x + draw.width) && (draw_location.x < camera.x + draw_area.width) &&
				(camera.y < draw_location.y + draw.height) && (draw_location.y < camera.y + draw_area.height))
			{
				if (HitBox(chip))
				{
					ret = true;
					break;
				}
			}
		}
	}

	return ret;
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
bool EnemyBulletBase::HitPlayerBullet(const BulletBase* player_bullet) const
{
	bool ret = false; //�߂�l
	if (HitSphere(player_bullet))
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//�_���[�W�̎擾
//-----------------------------------
int EnemyBulletBase::GetDamage() const
{
	return damage;
}

//-----------------------------------
//�^�C�v�̎擾
//-----------------------------------
ENEMY_TYPE EnemyBulletBase::GetType() const
{
	return type;
}