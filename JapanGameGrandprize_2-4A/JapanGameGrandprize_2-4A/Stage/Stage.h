#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>

#include "StageBuillder/StageBuilder.h"

#define CHIP_SIZE		40

class Player;

class Stage
{
private:
	//MapChip�I�u�W�F�N�g
	std::vector<MapChip*> mapchip;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//�}�b�v�z��f�[�^
	std::vector<std::vector<int>> map_data;

	//�w�i�摜
	int background_images;
	//�u���b�N�摜
	int block_images[110];

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
	void Update(Player* player);
	/// <summary>
	/// �X�e�[�W�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�e�[�W�̓ǂݍ���
	/// </summary>
	void LoadMap();

	/// <summary>
	/// �}�b�v�T�C�Y��Geter
	/// </summary>
	/// <returns>�\���̌^�F�}�b�v�T�C�Y</returns>	
	POINT GetMapSize(void) { POINT mapsize{ map_data.size(),map_data.at(0).size(), };  return mapsize; }
};