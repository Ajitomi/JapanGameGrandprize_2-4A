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
	end_deployment = false;

	location = spawn_location;
	radius = 160;
	images = new int[14];

	LoadDivGraph("Images/Enemy/SpecialMoves/barrier2_2.png", BARRIER_NUM, 2, 7, 384, 383,images);


		animation = 0;
	size = 2.0;
	angle = 0.0;
	count = 0;
	durability = DURABILITY;
	old_durability = durability;
	alpha = 255;
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



	if (!end_deployment)
	{
		Deployment();
	}
	else
	{
		alpha = static_cast<int>(255 * (static_cast<double>(durability) / DURABILITY));
		if (count % static_cast<int>(BARRIER_ANIMATION * 2.5) == 0)
		{
			animation = (++animation) % 3;
		}

	}
	
}

//�o���A�̓W�J
void LastBossBarrier::Deployment()
{

	
	if (count % BARRIER_ANIMATION == 0)
	{
		animation++;
	}
	if (9 < animation)
	{
		end_deployment = true;
	}
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void LastBossBarrier::HitBullet(const BulletBase* bullet)
{

	durability -= bullet->GetDamage();
	if (durability < 0)
	{
		durability = 0;
	}
}

//-----------------------------------
//�`��
//-----------------------------------
void LastBossBarrier::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (end_deployment)
	{
		DrawRotaGraphF(draw_location.x, draw_location.y, size, angle, images[animation + 8], TRUE);
	}
	else
	{
		DrawRotaGraphF(draw_location.x, draw_location.y, size, angle, images[animation], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

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

	if (durability <= 0)
	{
		ret = true;
	}

	return ret;
}