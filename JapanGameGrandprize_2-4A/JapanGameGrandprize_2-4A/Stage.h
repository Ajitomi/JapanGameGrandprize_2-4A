#pragma once
#include "MapChip.h"
#include <vector>

#include "StageBuillder/StageBuilder.h"

class Stage
{
private:
	//MapHip�I�u�W�F�N�g
	std::vector<MapChip*> mapchip;

#ifdef STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//�w�i�摜
	int background_images;
	//�u���b�N�摜
	int block_images[100];

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Stage();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Stage();
	/// <summary>
	/// �X�e�[�W�̍X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �X�e�[�W�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�e�[�W�̓ǂݍ���
	/// </summary>
	void LoadMap();
};

