#pragma once
#include "Stage_Element_Base.h"

class Element_DamageWall : public Stage_Element_Base
{
private:

public:

	//�R���X�g���N�^
	Element_DamageWall(MapChip* mapchip, int* image);
	//�f�X�g���N�^
	~Element_DamageWall();
	//�X�V
	void Update(Player *player);
	//�`��
	void Draw() const;


};