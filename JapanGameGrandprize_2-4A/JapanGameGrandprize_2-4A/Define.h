#pragma once

#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)
#define GRAVITY 10


//�������\����
struct Compound
{
	int warter;				//��
	int carbon_dioxide;		//��_���Y�f
	int ozone;				//�I�]��
	int sulfuric_acid;		//���_
	int hydrochloric_acid;	//���_
	int alcohol;			//�A���R�[��
	int tear_gas;			//�×܃K�X
	int suger;				//����
	int ammonium_chloride;  //�����A�����j�E��
	int acetic_acid;		//�|�_
	int propane;			//�v���p��
	int uranium;			//�E����
};

enum class Attribute
{
	normal = 0,
	explosion,
	melt,
	poison,
	paralysis,
	heal
};

//���S���W
struct Location
{
	float x;	//���S���W(x)
	float y;	//���S���W(y)
};

//�T�C�Y
struct Area
{
	float height;	//�c
	float width;	//��
};