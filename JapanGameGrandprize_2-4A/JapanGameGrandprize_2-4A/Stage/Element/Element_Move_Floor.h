#pragma once
#include "Stage_Element_Base.h"
#include <windef.h>

#define MOVE_START_TIME 10

class Element_Move_Floor : public Stage_Element_Base
{
private:
	
	//true=����,false=�~�܂�
	bool is_move;
	//�ړI�ʒu
	Location next_location;
	//�ړ����x
	Location speed;
	//�ړ��J�n�܂ł̎���
	short move_timer;
	//true=�������̖ړI�n�I�u�W�F�N�g,false=������
	bool is_goal_object;
public:

	//�������̃R���X�g���N�^
	Element_Move_Floor(short type, std::vector<int> images, Location location, Area area);
	//�������i�ڕW�n�_�̃R���X�g���N�^)
	Element_Move_Floor(short type, Location location);
	~Element_Move_Floor();
	
	//�X�V
	void Update(Player* player)override;

	//�ڕW�ʒu�̐ݒ�
	void SetLocation(Location location)override;
	//void SetNextLocation(Location next_location) { this->next_location = next_location; }
};