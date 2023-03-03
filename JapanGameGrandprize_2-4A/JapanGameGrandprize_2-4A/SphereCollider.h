#pragma once
#include "define.h"
#include "ColliderBase.h"

class SphereCollider :public ColliderBase
{
protected:

	int radius;			//���a
public:
	SphereCollider():ColliderBase()
	{
		radius = 5;
	}
	SphereCollider(Location location) :ColliderBase(location)
	{
		radius = 5;
	}

	//SphereCollider�����蔻��
	bool HitSphere(const SphereCollider* sphere_collider) const;

	//BoxCollider�����蔻��
	bool HitBox(const class BoxCollider* box_collider) const;

	bool HitLine(const class LineCollider* line_collider) const;

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