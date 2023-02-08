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

}

//------------------------------------
// �X�V
//------------------------------------
void StageBuilder::Update()
{
	{
		int x, y;
		GetMousePoint(&x, &y);
		mouse_pos.x = (float)x;
		mouse_pos.y = (float)y;
	}
}

//------------------------------------
// �`��
//------------------------------------
void StageBuilder::Draw()const
{
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 2, 10, 0xFFFFFF);
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 1, 10, 0x000000);
}

//------------------------------------
// �}�b�v�`�b�v�̍쐬
//------------------------------------
MapChip* StageBuilder::MakeMapChip()
{
	return new MapChip(&block_images[0],
		{ mouse_pos.x,mouse_pos.y },
		{ MAP_CHIP_SIZE,MAP_CHIP_SIZE });
}

//------------------------------------
// 
//------------------------------------


//------------------------------------
// 
//------------------------------------
