#pragma once
#include "Element.h"
class Element_MoveFloor :
	public Stage_Element
{
private:
	//���\�[�X
	int image;

	int se;

public:
	Element_MoveFloor();
	~Element_MoveFloor();
	void Update() override;
	void Draw() const override;
};

