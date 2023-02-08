#pragma once
#include "MapChip.h"
#include <vector>

class Stage
{
private:
	//MapChip�I�u�W�F�N�g
	std::vector<MapChip*> mapchip;

	//�}�b�v�z��f�[�^
	std::vector<std::vector<int>> map_data;

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

