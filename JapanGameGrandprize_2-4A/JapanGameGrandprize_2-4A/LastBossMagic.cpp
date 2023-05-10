#include "LastBossMagic.h"
#include "CameraWork.h"

//�摜����
#define MAGIC_IMAGES 10

//�X�^���o�C�̎���
#define STANDBY_TIME 60

//�A�j���[�V����
#define MAGIC_ANIMATION 5

//���@�͈̔�
#define MAGIC_AREA 60

//���@�U���̃_���[�W
#define MAGIC_DAMAGE 10

enum class MAGIC_TYPE 
{
	SLASH = 0,
	THUNDER
};

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossMagic::LastBossMagic()
{
	standby = true;
	can_delete = false;
	Location camera = CameraWork::GetCamera();

	Location spawn_location;
	spawn_location.x = MAGIC_AREA + GetRand(SCREEN_WIDTH - (MAGIC_AREA * 2));
	spawn_location.y = MAGIC_AREA + GetRand(SCREEN_HEIGHT - (MAGIC_AREA * 3));

	location = spawn_location + camera;
	radius = 0;

	images = new int[MAGIC_IMAGES];

	switch (static_cast<MAGIC_TYPE>(GetRand(1)))
	{
	case MAGIC_TYPE::SLASH:
		LoadDivGraph("Images/Enemy/Magic/Slash.png", MAGIC_IMAGES, 5, 2, 192, 192, images);
		this->type = ENEMY_TYPE::NORMAL;
		break;
	case MAGIC_TYPE::THUNDER:
		LoadDivGraph("Images/Enemy/Magic/Thunder.png", MAGIC_IMAGES, 5, 2, 192, 192, images);
		this->type = ENEMY_TYPE::THUNDER;
		break;
	default:
		break;
	}

	size = 0.0;
	standby_time = STANDBY_TIME;

	animation = 0;
	argument = 0;
	damage = MAGIC_DAMAGE;
}

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossMagic::LastBossMagic(const Location spawn_location)
{
	standby = true;
	can_delete = false;

	location = spawn_location;
	radius = 0;

	images = new int[MAGIC_IMAGES];

		switch (static_cast<MAGIC_TYPE>(GetRand(1)))
		{
		case MAGIC_TYPE::SLASH:
			LoadDivGraph("Images/Enemy/Magic/Slash.png", MAGIC_IMAGES, 5, 2, 192, 192, images);
			this->type = ENEMY_TYPE::NORMAL;
			break;
		case MAGIC_TYPE::THUNDER:
			LoadDivGraph("Images/Enemy/Magic/Thunder.png", MAGIC_IMAGES, 5, 2, 192, 192, images);
			this->type = ENEMY_TYPE::THUNDER;
			break;
		default:
			break;
		}

	size = 0.0;
	standby_time = STANDBY_TIME;

	animation = 0;
	argument = 0;
	damage = MAGIC_DAMAGE;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
LastBossMagic::~LastBossMagic()
{
	for (int i = 0; i < MAGIC_IMAGES; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;
}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBossMagic::Update()
{
	if (standby) //�X�^���o�C��
	{
		standby_time--;
		if (standby_time % MAGIC_ANIMATION == 0)
		{
			if (size < 1.0)
			{
				size += 0.2;
				radius = MAGIC_AREA * size;
			}
		}
		if (standby_time < 0)
		{
			standby = false;
			radius = 0;
			size = 0;
		}
	}
	else
	{
		animation++;
		if (animation % MAGIC_ANIMATION == 0)
		{
			argument++;
			if (size < 1.0)
			{
				size += 0.5;
				radius = MAGIC_AREA * size;
			}
			if (MAGIC_IMAGES - 1 < argument)
			{
				can_delete = true;
			}
		}
	}
}

//-----------------------------------
//�`��
//-----------------------------------
void LastBossMagic::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (standby) //�X�^���o�C��
	{
		DrawCircle(static_cast<int>(draw_location.x), static_cast<int>(draw_location.y),
			radius, 0xff0000, FALSE);
	}
	else
	{
		DrawRotaGraphF(draw_location.x, draw_location.y, 0.75, 0.0, images[argument], TRUE);
	}
}

//-----------------------------------
//�폜�\�t���O�̎擾
//-----------------------------------
bool LastBossMagic::GetCanDelete() const
{
	return can_delete;
}

//-----------------------------------
//�X�^���o�C��Ԃ̎擾
//-----------------------------------
bool LastBossMagic::GetDoStandby() const
{
	return standby;
}