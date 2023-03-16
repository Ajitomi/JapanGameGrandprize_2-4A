#include "Pause.h"
#include "DxLib.h"
#include "PadInput.h"

Pause::Pause()
{
	is_paused = false;
	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	pause_graph = 0;
	pause_effect_timer = 0;
}

Pause::~Pause()
{
	DeleteFontToHandle(title_font);
}

void Pause::Update()
{
	//�E�B�W�F�b�g����A�N�e�B�u�A�E�B���h�E���ŏ������ꂽ�ꍇ�Ƀ|�[�Y
	if (GetWindowActiveFlag() == FALSE || GetWindowMinSizeFlag() == TRUE) { 
		if (pause_graph == 0) {
			pause_graph = MakeGraph(1280, 720);
			GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);
		}
		is_paused = true; 
	}

	//START�{�^���Ń|�[�Y�؂�ւ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) { 
		if (pause_graph == 0) {
			pause_graph = MakeGraph(1280, 720);
			GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);
		}
		else { 
			DeleteGraph(pause_graph); 
			pause_graph = 0;
			pause_effect_timer = 0;
		}
		is_paused = !is_paused; 
	}

	

}

void Pause::Draw()
{
	if (pause_effect_timer < 50) {
		pause_effect_timer++;
		if (pause_effect_timer % 5 == 0) {
			GraphFilter(pause_graph, DX_GRAPH_FILTER_GAUSS, 16, 70);
		}
	}

	DrawGraph(0, 0, pause_graph, FALSE);

	DrawStringToHandle(GetDrawCenterX("�|�[�Y", title_font), 100, "�|�[�Y", 0xF4948E, title_font, 0x000000);
}

int Pause::GetDrawCenterX(const char* string, int font_handle)const {

	//��ʕ�
	const int screenX = 1280;

	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}