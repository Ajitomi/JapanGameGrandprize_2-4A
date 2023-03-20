#pragma once
#include "Stage_Element_Base.h"
#include <windef.h>
class Element_Move_Floor : public Stage_Element_Base
{
private:
	//true=����,false=�~�܂�
	bool is_move;
	bool is_start_point;
	//�ړI�ʒu
	Location next_location;
	//�ړ����x
	Location speed;
public:
	Element_Move_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	~Element_Move_Floor();
	
	//�X�V
	void Update(Player* player)override;
};

