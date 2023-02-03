#pragma once
#include "define.h"


class SphereCollider
{
protected:
	Location location;	//���S���W
	int radius;			//���a
public:

	//SphereCollider�����蔻��
	bool HitSphere(SphereCollider* sphere_collider);

	//BoxCollider�����蔻��
	bool HitBox(class BoxCollider* box_collider);

	//���S���W�̎擾
	Location GetLocation() const 
	{
		return location; 
	}

	//���a�̎擾
	int GetRadius() const
	{
		return radius;
	}

	//���S���W�̐ݒ�
	void SetLocation(Location location) 
	{
		this->location = location;
	}

};

