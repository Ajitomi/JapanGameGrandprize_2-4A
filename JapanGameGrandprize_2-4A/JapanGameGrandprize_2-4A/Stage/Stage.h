#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"

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

	//���������I�u�W�F�N�g�̍��W	�\����
	POINT collision_chip;

	//�������Ă������		�\����
	//X[�E:1, -��:-1], Y[��:1, ��:-1]
	POINT collision_dir;

	//�������Ă������	(�l�n���p)	�\����
	POINT collision_dir_w;
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
	std::vector<MapChip*> GetMapChip() const { return mapchip; };

	/// <summary>
	/// **�v���C���[�ƃX�e�[�W�̓����蔻��p**
	/// ���������}�b�v�`�b�v�̕�����Getter
	/// </summary>
	/// <returns>POINT�^(�\���̌^) X[�E:1, -��:-1], Y[��:1, ��:-1]</returns>	
	const POINT GetCollision_Chip() 
	{ 
		POINT w = collision_dir_w;  collision_dir_w = { 0, 0 };
		return w;
	}

	/// <summary>
	/// **�v���C���[�ƃX�e�[�W�̓����蔻��p**
	/// ���������}�b�v�`�b�v���W��Getter
	/// </summary>
	/// <returns>POINT�^(�\���̌^) X, Y</returns>	
	const POINT GetCollision_Chip_Location() 
	{ 
		POINT w = collision_chip;  collision_chip = { 0, 0 };
		return w;
	}
};