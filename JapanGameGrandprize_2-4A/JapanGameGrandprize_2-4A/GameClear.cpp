#include "GameClear.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DxLib.h"

GameClear::GameClear()
{
	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

}

GameClear::~GameClear()
{
}

AbstractScene* GameClear::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new GameMain();
	}

	return this;
}

void GameClear::Draw() const
{
	DrawStringToHandle(GetDrawCenterX("GameClear", title_font), 150, "GameClear", 0xffffff,title_font);
	DrawStringToHandle(GetDrawCenterX("Press A Button", title_font), 500, "Press A Button", 0xffffff, title_font);
	
}