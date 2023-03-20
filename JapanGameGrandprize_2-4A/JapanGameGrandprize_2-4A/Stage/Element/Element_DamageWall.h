#pragma once
#include "Stage_Element_Base.h"


class Element_DamageWall : public Stage_Element_Base
{
private:
	int anim_images[9];
	short anim_count;
	std::vector<int> images;

public:

	//�R���X�g���N�^
	Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	//�f�X�g���N�^
	~Element_DamageWall();
	//�X�V
	void Update(Player *player) override;


};