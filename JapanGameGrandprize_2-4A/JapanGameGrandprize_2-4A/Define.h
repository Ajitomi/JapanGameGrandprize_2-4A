#pragma once

#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)
#define GRAVITY 10

//���f�\����
struct ElementItem
{
	int oxygen;      //�_�f
	int hydrogen;	 //���f
	int nitrogen;	 //���f
	int carbon;		 //�Y�f
	int sulfur;		 //����
	int chlorine;	 //���f
	int uranium;	 //�E����
};


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

struct Explosion
{

};

struct Melt
{

};

struct Poison
{

};

struct Paralysis
{

};

struct Heal
{

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