#include "LastBossBarrier.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "NormalBullet.h"

//�ϋv�l
#define DURABILITY 500

//�摜����
#define BARRIER_NUM 14

//�G�t�F�N�g�̖{�̂̃A�j���[�V����
#define BARRIER_ANIMATION 2

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossBarrier::LastBossBarrier(const Location spawn_location)
{
	location = spawn_location;
	radius = 80;
	images = new int[14];

	LoadDivGraph("Images/Enemy/SpecialMoves/barrier2_2.png", BARRIER_NUM, 2, 7, 384, 383,images);

	animation = 0;
	size = 1.0;
	angle = 0.0;
	count = 0;
	durability = DURABILITY;
	old_durability = durability;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
LastBossBarrier::~LastBossBarrier()
{
	for (int i = 0; i < BARRIER_NUM; i++)
	{
		DeleteGraph(images[i]);
	}
	delete[] images;
}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBossBarrier::Update()
{
	count++;

	if (animation < 9)
	{
		if (count % BARRIER_ANIMATION == 0)
		{
			animation++;
		}
	}
	else
	{
		if ((durability % 100) < (old_durability % 100))
		{
			animation++;
		}
	}
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void LastBossBarrier::HitBullet(const BulletBase* bullet)
{
	old_durability = durability;

	durability -= bullet->GetDamage();
}

//-----------------------------------
//�`��
//-----------------------------------
void LastBossBarrier::Draw() const
{
	Location draw_location = CameraWork::GetCamera();

	draw_location = draw_location + location;
	DrawRotaGraphF(draw_location.x, draw_location.y, size, angle, images[animation], TRUE);
}

//-----------------------------------
//�ϋv�l�o�[�̕`��
//-----------------------------------
void LastBossBarrier::DrawDurabilityBar() const
{
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x000000, TRUE);
	DrawBox(160, 10, 160 + (960 * (static_cast<float>(durability) / DURABILITY)), 40, 0xffffff, TRUE);
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x8f917f, FALSE);
}

//-----------------------------------
//�j�󂳂ꂽ
//-----------------------------------
bool LastBossBarrier::Break() const
{
	bool ret = false;

	if (durability < 0)
	{
		ret = true;
	}

	return ret;
}