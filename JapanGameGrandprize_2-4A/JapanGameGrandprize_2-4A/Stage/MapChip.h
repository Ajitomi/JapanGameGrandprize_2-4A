#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f

class MapChip :
	public BoxCollider
{
public:

	//�R���X�g���N�^
	MapChip();
	//�R���X�g���N�^
	MapChip(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	virtual ~MapChip();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw() const;

	/// <summary>
	/// �����蔻��͈͂�Setter
	/// </summary>
	void SetArea(Area set_area)
	{
		area.height = set_area.height;
		area.width = set_area.width;
	}

	/// <summary>
	/// �摜��Setter
	/// </summary>
	void SetImage(int image) 
	{
		this->image = image;
	}
protected:

	
	int image;
	Area image_size;
	float ex_rate;
};