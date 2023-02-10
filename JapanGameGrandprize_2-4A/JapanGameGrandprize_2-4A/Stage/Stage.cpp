#include "Stage.h"
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define STAGE_NAME	"debugStage";
#define STAGE_NAME	"sample_stage";


//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Stage::Stage()
{
	if (LoadDivGraph("Images/Stage/map_chips.png", 100, 10, 10, 40, 40, block_images + 1) == -1)
	{
		throw "Images/Stage/map_chips.png";
	}

	//�}�b�v�f�[�^�̓ǂݍ���
	LoadMap();

	//�}�b�v�`�b�v�̕`������Z�b�g
	for (float y = 0; y < map_data.size(); y++) 
	{
		for (float x = 0; x < map_data.at(0).size(); x++) 
		{
			int i = map_data.at(y).at(x);
			mapchip.push_back(new MapChip(&block_images[i], { x * MAP_CHIP_SIZE,y * MAP_CHIP_SIZE}, { 40,40 }));
		}
	}
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Stage::~Stage()
{

	//�}�b�v�`�b�v�̕`����I�u�W�F�N�g���폜
	for (int i = 0; i < mapchip.size(); i++)
	{
		delete mapchip.at(i);
	}

	mapchip.clear();
	mapchip.shrink_to_fit();

	//�}�b�v�`�b�v�摜���폜
	for (int i = 0; i < 100; i++) 
	{
		DeleteGraph(block_images[i]);
	}
}

//-----------------------------------
// �X�V
//-----------------------------------
void Stage::Update()
{

	for (int i = 0; i < mapchip.size(); i++)
	{		
		mapchip.at(i)->Update();

	}
}

//-----------------------------------
// �`��
//-----------------------------------
void Stage::Draw()
{

	//�}�b�v�`�b�v		�`��
	for (int i = 0; i < mapchip.size(); i++)
	{
		mapchip.at(i)->Draw();
	}
	
	
}

//-----------------------------------
// �}�b�v�Ǎ���
//-----------------------------------
void Stage::LoadMap()
{
	const char* stage_name = STAGE_NAME;


	char buf[37];
	sprintf_s(buf, sizeof(buf), "Data/Map_Data/%s.csv", stage_name);

	int FileHandle;
	if ((FileHandle = FileRead_open(buf)) == 0) 
	{
		exit(1);
	}

	char str[900];		//��s�̒���
	char* context;
	int i = 0, j = 0;

	while (FileRead_gets(str, sizeof(str), FileHandle) != -1)
	{

		char* tmp = strtok_s(str, ",", &context);

		map_data.push_back(std::vector<int>());
		while (tmp != NULL) 
		{

			map_data[i].push_back(std::stoi(tmp));

			tmp = strtok_s(NULL, ",", &context);
			j++;
		}
		j = 0;
		i++;
	}

	FileRead_close(FileHandle);
}