#pragma once
#include "define.h"
#include "ColliderBase.h"

class SphereCollider :public ColliderBase
{
protected:

	int radius;			//半径
public:
	SphereCollider():ColliderBase()
	{
		radius = 5;
	}
	SphereCollider(Location location) :ColliderBase(location)
	{
		radius = 5;
	}

	//描画
	virtual void Draw()const;

	//SphereCollider当たり判定
	bool HitSphere(const SphereCollider* sphere_collider) const;

	//BoxCollider当たり判定
	bool HitBox(const class BoxCollider* box_collider) const;

	bool HitLine(const class LineCollider* line_collider) const;

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