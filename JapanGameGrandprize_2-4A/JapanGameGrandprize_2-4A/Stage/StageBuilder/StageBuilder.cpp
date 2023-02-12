#include "DxLib.h"
#include "StageBuilder.h"
#include "Directory.h"
#include <string>


//------------------------------------
// �R���X�g���N�^
//------------------------------------
StageBuilder::StageBuilder()
{
	Directory::Init();
	mouse = new SphereCollider();
	mouse_pos = {};
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}
	mode = BRUSH_MODE;

	menu_cursor = 0;	
	arrow[0] = '>';
	for (int i = 1; i < MENU_NUM; i++)
	{
		arrow[i] = ' ';
	}
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
StageBuilder::~StageBuilder()
{
	delete mouse;
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
	UpdateMouse();
	
	if (KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE))mode = MENU_MODE;
	switch (mode)
	{
	case MENU_MODE:
		UpdateMenu();
		break;
	
	case BRUSH_MODE:
		UpdateBrush();
		break;
	
	case MODULATION_MODE:
		UpdateModulation();
		break;

	case SAVE_MODE:
		SaveStage();
		break;
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

#ifdef _DEBUG
	SetFontSize(16);
	for (int i = 0; i < map_chips.size(); i++)
	{
		int frame_x = (int)(map_chips[i]->GetLocation().x / MAP_CHIP_SIZE);
		int frame_y = (int)(map_chips[i]->GetLocation().y / MAP_CHIP_SIZE);

		DrawFormatString(0, i * 20, 0xFFFFFF, "�}�X x:%d y:%d  ���Wx:%.0lf y:%.0lf ",
			frame_x, frame_y,
			(double)frame_x * MAP_CHIP_SIZE, (double)frame_y * MAP_CHIP_SIZE);
	}

#endif
	if (mode == MENU_MODE)
	{
		DrawMenu();
	}
	if (mode == SAVE_MODE)
	{
		int l_font_size = 16;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		DrawBox(600, 300,
			600 + l_font_size * 10, 300 + l_font_size * 10, 0x000000, TRUE);
		DrawBoxAA(600, 300,
			600.f + l_font_size * 10, 300.f + l_font_size * 10, 0xFFFFFF, FALSE, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		static bool test = false;

		if (!test)
		{
			bool ret;
			ret = Directory::OpenMain();
			ret = Directory::Open("\\Stage\\StageBuilder\\dat\\");
			test = true;
		}

		FILEINFO file_info;
		string file_name(Directory::GetCurrent());
		file_name += '\\*';

		__int64 find_handle = FileRead_findFirst(
			"C:\\PG-R4\\C++\\JapanGameGrandprize_2-4A\\JapanGameGrandprize_2-4A\\JapanGameGrandprize_2-4A\\Stage\\StageBuilder\\dat\\*",
			&file_info);
		if (find_handle != (__int64)-1)
		{
			
			int y = 0;
			do
			{
			
				// �t�@�C�����ƃt�H���_���t�@�C�����̏���`��
				DrawFormatString(600 + l_font_size, 300 + l_font_size + y, 
					GetColor(255, 255, 255), "%s %s", file_info.Name, file_info.DirFlag ? "�t�H���_" : "�t�@�C��");

				// �`��y���W�����炷
				y += 16;
				// �����Ɉ��������鎟�̃t�@�C���̏����擾�A���������烋�[�v�𔲂���
			} while (FileRead_findNext(find_handle, &file_info) >= 0);
				
			// �����n���h���̌�n��
			FileRead_findClose(find_handle);
		}

	}
}

//------------------------------------
// ���j���[���[�h�̍X�V
//------------------------------------
void StageBuilder::UpdateMenu()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_S) || KeyManager::OnKeyClicked(KEY_INPUT_DOWN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor++;

		if (menu_cursor > MENU_NUM - 1)
		{
			menu_cursor = 0;
		}

		arrow[menu_cursor] = tmp;
	}

	if (KeyManager::OnKeyClicked(KEY_INPUT_W) || KeyManager::OnKeyClicked(KEY_INPUT_UP))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor--;
		if (menu_cursor < 0)
		{
			menu_cursor = MENU_NUM - 1;
		}

		arrow[menu_cursor] = tmp;
	}
	
	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		mode = menu_cursor;
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}
}

//------------------------------------
// �u���V���[�h�̍X�V
//------------------------------------
void StageBuilder::UpdateBrush()
{
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		MakeMapChip();
	}
}

//------------------------------------
// ���f�����[�V�������[�h�̍X�V
//------------------------------------
void StageBuilder::UpdateModulation()
{
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		mouse->SetLocation(mouse_pos);
		for (int i = 0; i < map_chips.size(); i++)
		{
			if (mouse->HitBox(map_chips[i]))
			{
				delete map_chips[i];
				map_chips.erase(map_chips.begin() + i);
				break;
			}
		}
	}
}

//------------------------------------
// �}�E�X�̍X�V
//------------------------------------
void StageBuilder::UpdateMouse()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse_pos.x = (float)x;
	mouse_pos.y = (float)y;
}

//------------------------------------
// ���j���[�̕`��
//------------------------------------
void StageBuilder::DrawMenu()const
{
	int font_size = 20;
	int current = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(0, 0, 320, font_size * MENU_NUM,0x000000,TRUE);
	DrawBoxAA(0, 0, 320, (float)(font_size * MENU_NUM), 0xFFFFFF, FALSE, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetFontSize(font_size);
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c BRUSH_MODE", arrow[current]);
	current++;
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c MODULATION_MODE", arrow[current]);
	current++;
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c SAVE", arrow[current]);
	current++;
}

//------------------------------------
// �i�q�̕`��
//------------------------------------
void StageBuilder::DrawFrame()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_HEIGHT; i++)
	{
		DrawLineAA(0, i * MAP_CHIP_SIZE, SCREEN_WIDTH, i * MAP_CHIP_SIZE, 0xFFFFFF);
	}

	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_WIDTH; i++)
	{
		DrawLineAA(i * MAP_CHIP_SIZE, 0, i * MAP_CHIP_SIZE, SCREEN_HEIGHT, 0xFFFFFF);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//------------------------------------
// �}�b�v�`�b�v�̍쐬
//------------------------------------
void StageBuilder::MakeMapChip()
{
	float pos_x = (int)(mouse_pos.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE;
	float pos_y = (int)(mouse_pos.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE;
	map_chips.push_back(new MapChip(&block_images[0],
		{ pos_x + MAP_CHIP_SIZE / 2,pos_y + MAP_CHIP_SIZE / 2 },
		{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// CSV�t�@�C���֏����o��
//------------------------------------
void StageBuilder::SaveStage()
{
//	FILE* fp = NULL;
//	char* main_dir = nullptr;
//	main_dir = _getcwd(main_dir, 256);
//	string path(main_dir);
//	path += "\\Stage\\StageBuilder";
//	_chdir(path.c_str());
//
//
//	string file_name;
//	
//	file_name += ".csv";
//	//fopen_s(&fp, file_name.c_str(), "a");
//
//	_chdir(main_dir);

}

//------------------------------------
// 
//------------------------------------
