#pragma once
#include "Stage_Element_Base.h"

class Element_DamageWall : public Stage_Element_Base
{
private:

public:

	//�R���X�g���N�^
	Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//�f�X�g���N�^
	~Element_DamageWall();
	//�X�V
	void Update(Player *player) override;
	////�`��
	//void Draw() const override;


};