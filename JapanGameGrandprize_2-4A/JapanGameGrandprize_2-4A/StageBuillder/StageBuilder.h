#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include <vector>

class StageBuilder
{
private:
	Location mouse_pos;
	//�u���b�N�摜
	int block_images[100];

public:
	//�R���X�g���N�^
	StageBuilder();
	//�f�X�g���N�^
	~StageBuilder();
	//�X�V
	void Update();
	//�`��
	void Draw()const;

	//�}�b�v�`�b�v���쐬����
	MapChip* MakeMapChip();
};

