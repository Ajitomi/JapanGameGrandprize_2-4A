#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include "../../LineCollider.h"
#include "PolyLine.h"
#include <vector>

//���[�h�̐��Ƃ��̎��------
#define MENU_NUM 4
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2
#define LOAD_MODE 3
//--------------------------

//�u���V�̐��Ƃ��̎��---------
#define CLASS_NUM 2	
#define MAP_CHIP 0
#define POLY_LINE 1
//-----------------------------

#define ARROW_NUM 16

using namespace std;

class StageBuilder
{
private:
	const char* class_name[CLASS_NUM] =
	{
		"default_map_chip",
		"poly_line"
	};

	//�C���^�t�F�[�X
	SphereCollider* mouse;
	ColliderBase* select_collider;
	int menu_cursor;
	char arrow[ARROW_NUM];

	//�f�t�H���g�}�b�v�`�b�v
	int block_images[110];		//�u���b�N�摜
	vector<MapChip*> map_chips;

	//�ۗ����̃X�t�B�A
	vector<SphereCollider*> pending_sphere;

	//�c�[���p
	int mode;
	int current_brush;

	//todo:�e�X�g ��Xvector�z��ɂ��ĉ^�p����
	class PolyLine* line;
	LineCollider_t* line_collider;

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
	//�Z�[�u���[�h�̍X�V
	void UpdateSave();
	//���[�h���[�h�̍X�V
	void UpdateLoad();
	//�}�E�X�̍X�V
	void UpdateMouse();

	//���[�h���Ƃɕ����ꂽ�`��
	void DrawWhichMode()const;
	//���j���[���[�h�̕`��
	void DrawMenu()const;
	//�Z�[�u���[�h�̕`��
	void DrawFileInfo()const;
	//�i�q�̕`��
	void DrawFrame()const;
	//�}�E�X�̕`��
	void DrawMouse()const;
	//�t�@�C���̕`��
	void DrawFile(float x, float y, const char* path, int font_size)const;
	//���݂̃u���V�ɂȂ��Ă���N���X��`��
	void DrawClassName()const;
	//�ۗ����̃X�t�B�A�̕`��
	void DrawSphere()const;
	//�ۗ����̃��C���̕`��
	void DrawLine(Location start, Location end)const;

	//�}�b�v�`�b�v���쐬����
	void MakeMapChip(); //�N���b�N�����Ƃ��p
	void MakeMapChip(float x, float y, float width, float height); //CSV�t�@�C������̓ǂݍ��ݗp

	//�R���W�����N���X���쐬����
	//�܂��
	void MakePolyLine();
	//�~
	void MakeSphere();
	//�ۗ����̃I�u�W�F�N�g�����Z�b�g����
	void Trash();

	//�t�@�C���J�E���g
	int FileCount(const char* path)const;

	//���j���[�I��
	void Select(int menu_max);

	const int* GetImage(int image_index)const;

	//CSV�t�@�C���ւ̏����o��(�V�K�ǉ�)
	void SaveStage(int stage_num);
	//�㏑���ۑ�
	void SaveStage(char* stage_name);
	//CSV�t�@�C������̓ǂݍ���
	void LoadStage(char* stage_name);
};