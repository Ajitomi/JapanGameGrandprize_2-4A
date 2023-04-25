#pragma once
#include "Debug.h"

#ifdef _STAGE_BUILDER
#include "../Define.h"
#include "../../TextureContainer.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include "../../LineCollider.h"
#include "PolyLine.h"
#include "ObjectBase.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>

//sphereCollider�͖�3000���x�Ȃ�t���[�����[�g�𗎂Ƃ����X�V�ł���


//���[�h�̐��Ƃ��̎��------
#define MENU_NUM 4
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2
#define LOAD_MODE 3
//--------------------------

//�u���V�̐��Ƃ��̎��---------
#define CLASS_NUM 4	
#define BRUSH_OBJECT 0
#define BRUSH_MAP_CHIP 1
#define BRUSH_BOX 2
#define BRUSH_POLY_LINE 3
//-----------------------------


//�摜�̐��Ƃ��̎��-----------------------------
#define IMAGE_NUM 6
#define YUKA_1 0
#define YUKA_2 1
#define KABE_1 2
#define KABE_2 3
#define KAIDANN_1 4
#define KAIDANN_2 5
//-----------------------------------------------

//�u���V���[�h�̃��j���[����-------------
#define CLOSE 0
#define SELECT_CLASS 1
#define SELECT_IMAGE 2
#define SELECT_COLLIDER 3
//---------------------------------------


#define ARROW_NUM 16

using namespace std;

class StageBuilder
{
private:

	const char* class_name[CLASS_NUM] =
	{
		"object",
		"default_map_chip",
		"box",
		"poly_line"
	};

	const char* image_name[IMAGE_NUM] =
	{
		"yuka_1"
		,"yuka_2"
		,"kabe_1"
		,"kabe_2"
		,"kaidann_1"
		,"kaidann_2"
	};

	//�C���^�t�F�[�X
	SphereCollider* mouse;
	ColliderBase* select_collider;
	int menu_cursor;
	char arrow[ARROW_NUM];

	//�f�t�H���g�}�b�v�`�b�v
	int block_images[110];		//�u���b�N�摜
	vector<MapChip*> map_chips;
	vector<BoxCollider*> box_collider;
	vector<PolyLine*>poly_lines;
	vector<ObjectBase*>objects;

	//�ۗ����̃X�t�B�A
	vector<SphereCollider*> pending_sphere;

	//�c�[���p
	int mode;
	int current_brush;
	int current_object_image;
	int current_object_collider;
	int brush_mode_state;


public:
	/*******************�X�V�`��n��*******************/
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
	//�u���V���[�h�̕`��
	void DrawBrushMode()const;

	//�����蔻��̕`�� + object��pivot --- collider�Ԃ̃x�N�g��
	void DrawCollider()const;

	//�i�q�̕`��
	void DrawFrame()const;
	//�}�E�X�̕`��
	void DrawMouse()const;
	//�t�@�C���̕`��
	void DrawFile(float x, float y, const char* path, int font_size)const;
	
	//���݂̃u���V�ɂȂ��Ă���N���X��`��
	void DrawClassName()const;
	//�N���X�I���̕`��
	void DrawSelectClass()const;
	//�摜�I���̕`��
	void DrawSelectImage()const;
	//�����蔻��I���̕`��
	void DrawSelectCollider()const;

	//�ۗ����̃X�t�B�A�̕`��
	void DrawSphere()const;
	//�ۗ����̃��C���̕`��
	void DrawLine(Location start, Location end)const;

	/**********************�@�\�n**************************/
	//�}�E�X���͂ɂ��I�u�W�F�N�g�̈ړ�
	void MovementByMouse();
	//�L�[�{�[�h���͂ɂ��I�u�W�F�N�g�̈ړ�
	void MovementByKey();

	//�I�u�W�F�N�g�̍폜
	void DeleteObject();

	//�I�u�W�F�N�g�̑I��
	void IsSelectedObject();

	//�܂���̕ό`
	bool TransformPolyLine();
	bool TransformPolyLine(PolyLine* poly_line);
	//��`�̕ό`
	bool TransformBox();
	bool TransformBox(BoxCollider* box);

	//�}�b�v�`�b�v���쐬����
	void MakeMapChip(); //�N���b�N�����Ƃ��p
	MapChip* MakeMapChip(float x, float y, float width, float height); //CSV�t�@�C������̓ǂݍ��ݗp

	//object�N���X���쐬����
	void MakeObject();

	//�R���W�����N���X���쐬����
	//�܂��
	bool MakePolyLine();
	//BoxCollider���쐬����
	void MakeBoxCollider();
	//�~
	void MakeSphere();
	//�ۗ����̃I�u�W�F�N�g�����Z�b�g����
	void Trash();

	//���j���[�I��
	void Select(int menu_max);

	//�N���X�I��
	void SelectClass();
	//�摜�I��
	void SelectImage();
	//�����蔻��I��
	void SelectCollider();


	/******************�t�@�C���ւ̏������ݓǂݍ��݌n*********************/
	//CSV�t�@�C���ւ̏����o��(�V�K�ǉ�)
	void SaveStage(int stage_num);
	//�㏑���ۑ�
	void SaveStage(char* stage_name);
	//CSV�t�@�C������̓ǂݍ���
	void LoadStage(char* stage_name);
	//�t�@�C���J�E���g
	int FileCount(const char* path)const;


	//�}�b�v�`�b�v�̕ۑ�
	void SaveMapChips(FILE* fp);
	//�܂���̕ۑ�
	void SavePolyLine(FILE* fp);
	//BoxCollider�̕ۑ�
	void SaveBoxCollider(FILE* fp);
	//�I�u�W�F�N�g�̕ۑ�
	void SaveObject(FILE* fp);

	//�}�b�v�`�b�v�̓ǂݍ���
	MapChip* LoadMapChip(istringstream* i_stringstream);
	//�܂���̓ǂݍ���
	PolyLine* LoadPolyLine(istringstream* i_stringstream);
	//BoxCollider�̓ǂݍ���
	BoxCollider* LoadBoxCollider(istringstream* i_stringstream);

};


#endif