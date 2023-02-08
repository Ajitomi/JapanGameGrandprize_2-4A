#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include <vector>
using namespace std;

class StageBuilder
{
private:
	Location mouse_pos;
	//�u���b�N�摜
	int block_images[100];
	vector<MapChip*> map_chips;

public:
	//�R���X�g���N�^
	StageBuilder();
	//�f�X�g���N�^
	~StageBuilder();
	//�X�V
	void Update();
	//�`��
	void Draw()const;

	//�}�E�X�̍X�V
	void MouseUpdate();
	//�i�q�̕`��
	void DrawFrame()const;

	//�}�b�v�`�b�v���쐬����
	void MakeMapChip();
};

