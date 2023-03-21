#include "Element_Move_Floor.h"

Element_Move_Floor::Element_Move_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, { MAP_CHIP_SIZE,MAP_CHIP_SIZE })
{
	this->type = type;
	this->location = location;
	next_location = { location.x + area.width ,location.y };
	this->area = { MAP_CHIP_SIZE,MAP_CHIP_SIZE };

	is_move = true;
	speed.x = 5.0f;
	speed.y = 0.0f;
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{
	Location location = this->GetLocation();

    if (location.x == next_location.x) {
        is_move = false;
    }

	//�ړI�ʒu�܂œ���
	if (is_move && location.x < next_location.x)
	{
		SetLocation({ location.x + speed.x , location.y + speed.y });
		//�ړI�ʒu��ʂ�߂�����ړI�ʒu�ɖ߂�
		if (location.x > next_location.x) {
			SetLocation(next_location);
		}
	}
}

    //if (/*�v���C���[����ɓ������Ă��鎞*/)
    //{
    //    player->SetLocation({ player->GetLocation().x + speed_x, player->GetLocation().y });
    //}

