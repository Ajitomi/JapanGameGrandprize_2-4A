#include "Element_Move_Floor.h"
#include "..//Player.h"

Element_Move_Floor::Element_Move_Floor(short type,
	std::vector<std::shared_ptr<Stage_Element_Base>> element,
	std::vector<int> images, Location location, Area area)
	: Stage_Element_Base(element, &images.at(0), location, { MAP_CHIP_SIZE,MAP_CHIP_SIZE })
{

	this->type = type;
	this->location = location;

	this->area = { MAP_CHIP_SIZE - 20,MAP_CHIP_SIZE };
	margin_area = { 0.0f,0.0f };

	is_move = false;
	speed.x = 5.0f;
	speed.y = 0.0f;

	next_location = { location.x + area.width ,location.y };
	move_timer = 0;
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{
	//debug
	if (CheckHitKey(KEY_INPUT_A))
	{
		SetLocation({ 200.f,500.f });
	}

	Location location = this->GetLocation();
	Location p_location = player->GetLocation();
	HIT_DIRECTION hit_direction = std::get<1>(HitPlayer(player));

	if (hit_direction == HIT_DIRECTION::UP)
	{
		if (MOVE_START_TIME <= move_timer++)
		{
			is_move = true;
		}
	}

    if (location.x == next_location.x) 
	{
        is_move = false;
		move_timer = 0;
    }

	
	//���������ł���ꍇ
	if (is_move)
	{
		//�ړI�ʒu�܂œ���
		if (location.x != next_location.x)
		{
			SetLocation({ location.x + speed.x , location.y + speed.y });
			//�ړI�ʒu��ʂ�߂�����ړI�ʒu�ɖ߂�
			if (location.x > next_location.x)
			{
				SetLocation(next_location);
			}
		}
		//�v���C���[������Ă���Ƃ��A�v���C���[���W�ɏ��̃X�s�[�h�����Z����
		if (hit_direction == HIT_DIRECTION::UP && player->GetState() != PLAYER_STATE::JUMP)
		{
			player->SetLocation({ p_location.x + speed.x,p_location.y + speed.y });
		}

	}

	
	/*if (abs(abs(location.x - p_location.x) <= MAP_CHIP_SIZE
		&& abs(location.y - p_location.y) <= MAP_CHIP_SIZE))
	{
		player->SetLocation({ p_location.x + speed.x,p_location.y - speed.y });
	}*/
}

    //if (/*�v���C���[����ɓ������Ă��鎞*/)
    //{
    //    player->SetLocation({ player->GetLocation().x + speed_x, player->GetLocation().y });
    //}