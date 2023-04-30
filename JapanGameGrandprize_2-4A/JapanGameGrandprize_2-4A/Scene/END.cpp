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
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
END::~END()
{
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

		// �J�[�\���������Ă���ꍇ�A�����F�ƕ����O�g�F�𔽓]������
		if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}

		DrawStringToHandle(GetDrawCenterX(menu_items[i], menu_font), i * margin_y + base_y, menu_items[i], color, menu_font, border_color);
	}


}