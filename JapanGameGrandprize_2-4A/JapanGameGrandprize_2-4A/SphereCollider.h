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

	//�`��
	virtual void Draw()const;

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const class BoxCollider* box_collider) const override;

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(const class LineCollider* line_collider) const override;

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