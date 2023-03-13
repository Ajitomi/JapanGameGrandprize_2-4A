#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"
#include "Element/Stage_Element_Base.h"

#define CHIP_SIZE	40

class Player;

class Stage_Element;

class Stage
{
private:

	//�I�u�W�F�N�g�ϐ�
	Player* player;
	Stage_Element* element;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//�}�b�v�z��f�[�^
	std::vector<std::vector<int>> map_data;

	//�w�i�摜
	int background_images;
	//�u���b�N�摜
	int block_images[110];


protected:

	//MapChip�I�u�W�F�N�g
	std::vector<MapChip*> mapchip;
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
	/// Stage�N���X��Player�I�u�W�F�N�g��n��Setter
	/// </summary>
	/// <param name = "*player">Player�I�u�W�F�N�g�|�C���^</param>
	void SetPlayer(Player *player) { this->player = player; }

	/// <summary>
	/// �}�b�v�T�C�Y��Geter
	/// </summary>
	/// <returns>�\���̌^�F�}�b�v�T�C�Y</returns>	
	POINT GetMapSize(void) const
	{ 
		POINT mapsize{ map_data.at(0).size(),map_data.size() }; 
		return mapsize; 
	}

	/// <summary>
	/// �}�b�v�`�b�v�I�u�W�F�N�g��Getter
	/// </summary>
	/// <returns>�x�N�^�[�^(MapChip�I�u�W�F�N�g�^)�FMapChip</returns>	
	/// ���S�v�f�����[�v���Ďg��Ȃ�����
	std::vector<MapChip*> GetMapChip() const;

	/// <summary>
	/// Element�I�u�W�F�N�g��Getter
	/// </summary>
	/// <returns>�x�N�^�[�^(Stage_Element_Base�I�u�W�F�N�g�^)�FStage_Element_Base</returns>	
	/// ���S�v�f�����[�v���Ďg��Ȃ�����
	std::vector<Stage_Element_Base*> GetElement_MapChip() const;
};