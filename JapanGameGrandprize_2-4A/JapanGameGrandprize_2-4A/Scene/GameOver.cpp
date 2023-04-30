#include "GameOver.h"
#include "DxLib.h"
#include "GameMain.h"
#include "../PadInput.h"
#include "Title.h"

#define FADE_TIME 120

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
GameOver::GameOver(short stage_num)
{
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Images/Scene/game_over.png");

	this->stage_num = stage_num;

	select_menu = static_cast<int>(MENU::RETRY);

	input_margin = 0;

	fade_counter = 0;
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
GameOver::~GameOver()
{
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteGraph(background_image);
	SetDrawBright(255, 255, 255);
}

//-----------------------------------
//�X�V
//-----------------------------------
AbstractScene* GameOver::Update()
{
	// ����Ԋu����
	const int max_input_margin = 15;

	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin)
	{
		input_margin++;
	}
	else {

		if (std::abs(PAD_INPUT::GetLStick().y) > stick_sensitivity) {

			select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
			input_margin = 0;

		}
	}


	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		input_margin = 0;
		MENU current_selection = static_cast<MENU>(select_menu);
		switch (current_selection)
		{
		case MENU::RETRY:
			return new GameMain(stage_num);
			break;

		case MENU::TITLE:
			return new Title();
			break;

		default:
			printfDx("�������ȋ@�\�ł��B\n");
			break;
		}

	}

	

	if (fade_counter < FADE_TIME)
	{
		fade_counter++;
	}
	

	return this;
}

//-----------------------------------
//�`��
//-----------------------------------
void GameOver::Draw() const
{

	const int fade_time = FADE_TIME;
	int bright = static_cast<int>((static_cast<float>(fade_counter) / FADE_TIME * 255));
	SetDrawBright(bright, bright, bright);

	DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("Game Over", title_font), 150, "Game Over", 0xFFFFFF, title_font, 0x000000);


	for (int i = 0; i < static_cast<int>(MENU::MENU_SIZE); i++)
	{
		// ������̍ŏ�Y���W
		const int base_y = 400;

		// �������Y���W�Ԋu
		const int margin_y = 100;

		// �����F
		int color = 0xFFFFFF;
		// �����O�g�F
		int border_color = 0x000000;
		// �����x
		int transparency = 180;

		// �J�[�\���������Ă���ꍇ�A�����F�ƕ����O�g�F�𔽓]������
		if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
			transparency = 255;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawStringToHandle(GetDrawCenterX(menu_items[i], menu_font), i * margin_y + base_y, menu_items[i], color, menu_font, border_color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
}