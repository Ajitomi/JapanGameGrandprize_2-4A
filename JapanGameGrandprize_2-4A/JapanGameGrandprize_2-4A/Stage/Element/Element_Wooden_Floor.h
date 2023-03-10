#pragma once
#include "Stage_Element_Base.h"


class Element_Wooden_Floor : public Stage_Element_Base
{
private:

	//���̓����蔻��͈�
	Area original_collision;

public:

	//�R���X�g���N�^
	Element_Wooden_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//�f�X�g���N�^
	~Element_Wooden_Floor();

	//�X�V
	void Update(Player* player) override;
	////�`��
	//void Draw() const override;


};