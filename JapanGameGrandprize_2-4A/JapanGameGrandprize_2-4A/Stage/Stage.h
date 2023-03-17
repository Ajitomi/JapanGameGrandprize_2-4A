#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"
#include "Element/Stage_Element_Base.h"
#include <set>

#define CHIP_SIZE	40

class Player;

class Stage_Element;

class Stage
{
public:
	struct ENEMY_LOCATION {
		short id;
		float x;
		float y;
	};

private:

	//�I�u�W�F�N�g�ϐ�
	Player* player;
	Stage_Element* element;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//�}�b�v�z��f�[�^
	std::vector<std::vector<int>> map_data;


	//�G�l�~�[�X�|�[���n�_Location�\����
	std::vector<ENEMY_LOCATION> enemy_init_location;

	//�G�l�~�[��ID
	std::set<short> enemy_id{ 200,201,202,203,204,205,206,207,208,209,210 };

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

	
	/// <summary>
	///�G�l�~�[�X�|�[��Location�\����	Getter
	/// </summary>
	/// <returns>�x�N�^�[�^(ENEMY_LOCATION�\���̌^)</returns>	
	std::vector<ENEMY_LOCATION> GetEnemy_SpawnLocation() const { return enemy_init_location; }
};