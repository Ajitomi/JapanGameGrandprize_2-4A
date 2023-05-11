#pragma once
#include "Stage_Element_Base.h"

class Element_Wooden_Floor : public Stage_Element_Base
{
private:

	//���̉摜
	int original_image;

	//���̓����蔻��͈�
	Area original_collision;
public:

	//�R���X�g���N�^
	Element_Wooden_Floor(short type, Resource resource, Location location, Area area);
	//�f�X�g���N�^
	~Element_Wooden_Floor();

	//�X�V
	void Update(Player* player) override;
};