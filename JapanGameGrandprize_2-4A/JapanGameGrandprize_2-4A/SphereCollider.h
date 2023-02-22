#pragma once
#include "define.h"
#include "ColliderBase.h"

class SphereCollider :public ColliderBase
{
protected:
	int radius;			//半径
public:

	//SphereCollider当たり判定
	bool HitSphere(SphereCollider* sphere_collider);

	//BoxCollider当たり判定
	bool HitBox(class BoxCollider* box_collider);

	bool HitLine(class LineCollider* line_collider);

	//中心座標の取得
	Location GetLocation() const 
	{
		return location; 
	}

	//半径の取得
	int GetRadius() const
	{
		return radius;
	}

	//中心座標の設定
	void SetLocation(Location location) 
	{
		this->location = location;
	}
};