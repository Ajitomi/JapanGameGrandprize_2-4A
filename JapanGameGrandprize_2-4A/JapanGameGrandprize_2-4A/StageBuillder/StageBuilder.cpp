#include "DxLib.h"
#include "StageBuilder.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
StageBuilder::StageBuilder()
{
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}
	mouse_pos = {};
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
StageBuilder::~StageBuilder()
{
	for (int i = 0; i < map_chips.size(); i++)
	{
		delete map_chips[i];
	}
	map_chips.clear();
}

//------------------------------------
// �X�V
//------------------------------------
void StageBuilder::Update()
{
	KeyManager::Update(); //StageBuilder��ł����g��Ȃ����߁A�\�[�X�R�[�h�̎U��΂������Ă��܂��B
	MouseUpdate();
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		MakeMapChip();
	}
}

//------------------------------------
// �`��
//------------------------------------
void StageBuilder::Draw()const
{
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 2, 10, 0xFFFFFF);
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 1, 10, 0x000000);

	for (int i = 0; i < map_chips.size(); i++)
	{
		map_chips[i]->Draw();
	}

	DrawFrame();
}

//------------------------------------
// �}�E�X�̍X�V
//------------------------------------
void StageBuilder::MouseUpdate()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse_pos.x = (float)x;
	mouse_pos.y = (float)y;
}

//------------------------------------
// �i�q�̕`��
//------------------------------------
void StageBuilder::DrawFrame()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_HEIGHT; i++)
	{
		DrawLine(0, i * MAP_CHIP_SIZE, SCREEN_WIDTH, i * MAP_CHIP_SIZE, 0xFFFFFF);
	}

	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_WIDTH; i++)
	{
		DrawLine(i * MAP_CHIP_SIZE, 0, i * MAP_CHIP_SIZE, SCREEN_HEIGHT, 0xFFFFFF);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//------------------------------------
// �}�b�v�`�b�v�̍쐬
//------------------------------------
void StageBuilder::MakeMapChip()
{
	map_chips.push_back(new MapChip(&block_images[0],
		{ mouse_pos.x,mouse_pos.y },
		{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// 
//------------------------------------
