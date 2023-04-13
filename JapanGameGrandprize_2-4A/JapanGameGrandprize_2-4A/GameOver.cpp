#include "GameOver.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
GameOver::GameOver()
{
	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
GameOver::~GameOver()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
AbstractScene* GameOver::Update()
{
	if(PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new GameMain();
	}

	return this;
}

//-----------------------------------
//�`��
//-----------------------------------
void GameOver::Draw() const
{
	DrawStringToHandle(GetDrawCenterX("GameOver", title_font), 150, "GameOver", 0xffffff, title_font);
	DrawStringToHandle(GetDrawCenterX("Press A Button", title_font), 500, "Press A Button", 0xffffff, title_font);
}