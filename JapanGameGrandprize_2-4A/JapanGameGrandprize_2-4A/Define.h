#pragma once

//�v���C���[�������Ă��錳�f�̎��
#define PLAYER_ELEMENT 7

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

enum class ATTRIBUTE
{
	NORMAL = 0,
	EXPLOSION,
	MELT,
	POISON,
	PARALYSIS,
	HEAL
};

//���S���W
struct Location
{
	float x;	//���S���W(x)
	float y;	//���S���W(y)

	Location operator +(Location location)
	{
		Location ret;

		ret.x = this->x + location.x;
		ret.y = this->y + location.y;

		return ret;
	}

	Location operator -(Location location)
	{
		Location ret;

		ret.x = this->x - location.x;
		ret.y = this->y - location.y;

		return ret;
	}
};

//�T�C�Y
struct Area
{
	float height;	//�c
	float width;	//��
};

