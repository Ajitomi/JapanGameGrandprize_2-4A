#pragma once
#include"define.h"

#include"StageBuillder/Debug.h"
#include"DxLib.h"

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

#ifdef SHOW_COLLISION
	void DrawCollision()const
	{
		float x1 = location.x;
		float y1 = location.y;
	
		float x2 = location.x + area.width;
		float y2 = location.y + area.height;
		DrawBoxAA(x1, y1, x2, y2, 0xE9FF00, FALSE, 3);
	}
#endif
};