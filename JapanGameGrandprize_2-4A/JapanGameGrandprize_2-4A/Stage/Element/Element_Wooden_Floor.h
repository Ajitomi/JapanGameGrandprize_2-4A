#pragma once
#include "Element.h"
class Element_Wooden_Floor :
	public Stage_Element
{
protected:
	int image;
	Area image_size;
	float ex_rate;

public:

	//�R���X�g���N�^
	Element_Wooden_Floor();
	//�R���X�g���N�^
	Element_Wooden_Floor(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~Element_Wooden_Floor();
	//�X�V

	void Update(Player* player);


	//�`��
	virtual void Draw() const;
};

