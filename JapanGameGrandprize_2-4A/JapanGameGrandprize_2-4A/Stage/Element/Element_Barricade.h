#pragma once
#include "Stage_Element_Base.h"

class Element_Barricade : public Stage_Element_Base
{
public:
	enum class DIRECTION {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		CENTER
	};

private:
	
	DIRECTION direction;

public:


	//�R���X�g���N�^
	Element_Barricade(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area, Area margin_area, DIRECTION direction);
	//�f�X�g���N�^
	~Element_Barricade();
	//�X�V
	void Update(Player* player) override;

	/*void Draw()const override;*/


};