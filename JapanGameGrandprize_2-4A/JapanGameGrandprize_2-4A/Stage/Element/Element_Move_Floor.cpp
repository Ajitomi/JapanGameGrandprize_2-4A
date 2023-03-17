#include "Element_Move_Floor.h"

Element_Move_Floor::Element_Move_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : Stage_Element_Base(element, image, location, area)
{
	this->type = type;
	this->location = location;
	this->area = area;

	is_move = true;
	speed_x = 5.0f;
	speed_y = 0.0f;



	for (auto& e : element) {

		//	�������g�̃I�u�W�F�N�g�̏ꍇ�̓X�L�b�v
		if (this->GetLocation().x == e->GetLocation().x) { continue; }

		//�����̃I�u�W�F�N�g��
		if (e->GetLocation().x - this->GetLocation().x < 2000
			&& e->GetLocation().x - this->GetLocation().x > 0) {
			is_start_point = true;
			next_location = e->GetLocation();
	
		}
		
		else
		{
			is_start_point = false;
		}
	}
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{
	if (this->GetLocation().x == next_location.x) { return; }

	if (is_move && this->GetLocation().x < next_location.x)
	{
		float x = GetLocation().x;
		SetLocation({ x + speed_x , GetLocation().y});
	}
}

void Element_Move_Floor::Draw() const
{
	float x = location.x - area.width / 2;
	float y = location.y - area.height / 2;
	
	DrawBoxAA(x, y, x + area.width, y + area.height, 0xff0000, TRUE);
}
