#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include "../../LineCollider.h"
#include <vector>

#define MENU_NUM 4
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2
#define LOAD_MODE 3

#define ARROW_NUM 16

using namespace std;

class StageBuilder
{
private:
	SphereCollider* mouse;//����̂�
	Location mouse_pos;
	//�u���b�N�摜
	int block_images[100];
	vector<MapChip*> map_chips;

	int mode;

	int menu_cursor;
	char arrow[ARROW_NUM];

	//todo:�e�X�g�Ȃ̂ŏ��� �w�b�_�[��
	class LineCollider2* line;
	

public:
	//�R���X�g���N�^
	StageBuilder();
	//�f�X�g���N�^
	~StageBuilder();
	//�X�V
	void Update();
	//�`��
	void Draw()const;

	//���j���[���[�h�̍X�V
	void UpdateMenu();
	//�u���V���[�h�̍X�V
	void UpdateBrush();
	//���f�����[�V�������[�h�̍X�V
	void UpdateModulation();
	//�Z�[�u���[�h�̍X�V
	void UpdateSave();
	//���[�h���[�h�̍X�V
	void UpdateLoad();
	//�}�E�X�̍X�V
	void UpdateMouse();

	//���j���[���[�h�̕`��
	void DrawMenu()const;
	//�Z�[�u���[�h�̕`��
	void DrawFileInfo()const;
	//�i�q�̕`��
	void DrawFrame()const;
	//�t�@�C���̕`��
	void DrawFile(float x,float y,const char* path ,int font_size)const;

	//�}�b�v�`�b�v���쐬����
	void MakeMapChip();
	void MakeMapChip(float x,float y,float width,float height);

	//�t�@�C���J�E���g
	int FileCount(const char* path)const;

	//���j���[�I��
	void Select(int menu_max);

	const int* GetImage(int image_index)const;

	//CSV�t�@�C���ւ̏����o��(�V�K�ǉ�)
	void SaveStage(int stage_num);
	//�㏑���ۑ�
	void SaveStage(char* stage_name);
	//CSV�t�@�C������̓ǂݍ���
	void LoadStage(char* stage_name);
};

