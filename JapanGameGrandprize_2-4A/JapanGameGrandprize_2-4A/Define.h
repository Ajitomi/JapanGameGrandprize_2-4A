#pragma once

//�v���C���[�������Ă��錳�f�̎��
#define PLAYER_ELEMENT 7

#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)
#define GRAVITY 10 //�d��

#define EXPLOSION_MAX_NUM 13	//�����̉������̌�
#define POISON_MAX_NUM 18		//�Ł@�̉������̌�
#define MELT_MAX_NUM 13			//�n���̉������̌�
#define PARARYSIS_MAX_NUM 12	//��Ⴢ̉������̌�
#define HEAL_MAX_NUM 7			//�񕜂̉������̌�

#define GREEN GetColor(0,255,0)
#define RED GetColor(255,0,0)
#define YELLOW GetColor(255,239,0)

#define MAX_STRING 40			//�e�̖��O�̍ő啶����

enum class ATTRIBUTE
{
	NORMAL = 0,
	EXPLOSION,
	MELT,
	POISON,
	PARALYSIS,
	HEAL
};

struct ChemicalFormulaMaterial
{
	int carbon;		//�Y�f
	int hydrogen;	//���f
	int nitrogen;	//���f
	int oxygen;		//�_�f
	int sulfur;		//����
	int chlorine;	//���f
	int uranium;	//�E����
};

struct ChemicalFormulaParameter
{
	int number_of_bullets;
	int time;
	int damage_per_second;
	int damage;
	char chemical_formula_name[MAX_STRING];
	char chemical_formula[MAX_STRING];
	ATTRIBUTE atribute;
	ChemicalFormulaMaterial material;
	bool make_bool;
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

	Location operator /(Location location)
	{
		Location ret;

		ret.x = this->x / location.x;
		ret.y = this->y / location.y;

		return ret;
	}

	Location operator /(int num)
	{
		Location ret;

		ret.x = this->x / num;
		ret.y = this->y / num;

		return ret;
	}

	bool operator <(Location location)
	{
		bool ret;

		ret = (this->x < location.x) && (this->y < location.y);

		return ret;
	}

	bool operator >(Location location)
	{
		bool ret;

		ret = (this->x > location.x) && (this->y > location.y);

		return ret;
	}

	bool operator <=(Location location)
	{
		bool ret;

		ret = (this->x <= location.x) && (this->y <= location.y);

		return ret;
	}

	bool operator >=(Location location)
	{
		bool ret;

		ret = (this->x >= location.x) && (this->y >= location.y);

		return ret;
	}

	bool operator !=(Location location)
	{
		bool ret;

		ret = (this->x != location.x) || (this->y != location.y);

		return ret;
	}

	bool operator ==(Location location)
	{
		bool ret;

		ret = (this->x == location.x) && (this->y == location.y);

		return ret;
	}
};

//�T�C�Y
struct Area
{
	float height;	//�c
	float width;	//��
};