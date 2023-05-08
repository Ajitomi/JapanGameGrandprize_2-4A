#pragma once
#include "Stage_Element_Base.h"

class Element_Conveyor_Belt : public Stage_Element_Base
{
public:

	//�R���X�g���N�^
	Element_Conveyor_Belt(short type, std::vector<int> images, Location location, Area area);
	//�f�X�g���N�^
	~Element_Conveyor_Belt();
	//�X�V
	void Update(Player* player) override;
};