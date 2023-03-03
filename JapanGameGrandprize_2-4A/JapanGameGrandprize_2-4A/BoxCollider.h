#pragma once
#include"define.h"

#include"Stage/StageBuilder/Debug.h"
#include"DxLib.h"
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
protected:
	
	Area area; //�͈�
public:

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(const class SphereCollider* sphere_collider) const;

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const BoxCollider* box_collider) const;

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(const class LineCollider* line_collider) const;
	
	//���S���W�̎擾
	Location GetLocation()const;

	//���a�̎擾
	Area GetArea()const;

	//���S���W�̐ݒ�
	void SetLocation(Location location);

#ifdef _SHOW_COLLISION
	void DrawCollision()const
	{
		float x1 = location.x - (area.width / 2);
		float y1 = location.y - (area.height / 2);
	
		float x2 = x1 + area.width;
		float y2 = y1 + area.height;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawBoxAA(x1, y1, x2, y2, 0xE9FF00, FALSE, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
#endif
};