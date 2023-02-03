#pragma once
#include"define.h"


class BoxCollider
{
protected:
	Location location;	//���S���W
	Area area; //�͈�
public:

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(class SphereCollider* sphere_collider);

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(BoxCollider* box_collider);
	
	//���S���W�̎擾
	Location GetLocation()const;

	//���a�̎擾
	Area GetArea()const;

	//���S���W�̐ݒ�
	void SetLocation(Location location);
};