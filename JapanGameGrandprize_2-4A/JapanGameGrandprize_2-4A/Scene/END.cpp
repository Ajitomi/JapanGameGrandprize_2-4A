#include "END.h"
#include "DxLib.h"
#include "Title.h"
#include "../PadInput.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
END::END()
{
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Images/Scene/end.png");


	select_se = 0;
	decision_se = 0;

	input_margin = 0;

	select_menu = static_cast<int>(MENU::TITLE);

	if ((background_music = LoadSoundMem("Sounds/BGM/end.mp3")) == -1) {
		throw "Sounds/BGM/end.mp3";
	}

	if ((enter_se = LoadSoundMem("Sounds/SE/enter.mp3")) == -1) {
		throw "Sounds/SE/enter.mp3";
	}

	if ((cursor_move_se = LoadSoundMem("Sounds/SE/cursor_move.mp3")) == -1)
	{
		throw "Sounds/SE/cursor_move.mp3";
	}

	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
END::~END()
{
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteSoundMem(enter_se);
	DeleteSoundMem(cursor_move_se);
	DeleteGraph(background_image);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* END::Update()
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

			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
			select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
			input_margin = 0;

		}
	}


	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
		while (CheckSoundMem(enter_se)) {}

		input_margin = 0;
		MENU current_selection = static_cast<MENU>(select_menu);
		switch (current_selection)
		{
		case MENU::TITLE:
			return new Title();
			break;

		case MENU::EXIT:
			return nullptr;
			break;

		default:
			printfDx("�������ȋ@�\�ł��B\n");
			break;
		}

	}



	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void END::Draw()const
{
	DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("Thanks!", title_font), 100, "Thanks!", 0xE1D000, title_font, 0xFFFFFF);

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