#include "GameOver.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
GameOver::GameOver()
{

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
}

//-----------------------------------
//�`��
//-----------------------------------
void GameOver::Draw() const
{
	DrawString(100, 100, "GameOver", 0x000000);
}