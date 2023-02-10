#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include <vector>

#define MENU_NUM 3
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2

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
	char arrow[MENU_NUM];

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

	//�}�E�X�̍X�V
	void UpdateMouse();
	//���j���[���[�h�̕`��
	void DrawMenu()const;
	//�i�q�̕`��
	void DrawFrame()const;

	//�}�b�v�`�b�v���쐬����
	void MakeMapChip();

	//CSV�t�@�C���ւ̏����o��
	void SaveStage();
};

