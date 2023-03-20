#pragma once
#include "Stage_Element_Base.h"
class Element_Fall_Floor : public Stage_Element_Base
{
private:
	int anim_images[9];
	
	std::vector<int> images;

	
	bool is_flash;
	float fall_speed;
	
	enum class STATE {
		NONE,
		WORKING,
		FLASH,
		FALL,
	} state;

public:

	//�R���X�g���N�^
	Element_Fall_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	//�f�X�g���N�^
	~Element_Fall_Floor();
	//�X�V
	void Update(Player* player) override;



};