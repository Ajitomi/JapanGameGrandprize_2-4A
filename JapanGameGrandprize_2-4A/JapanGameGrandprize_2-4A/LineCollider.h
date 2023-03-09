#pragma once
#include "Define.h"
#include "Stage/StageBuilder/Debug.h"
#include "ColliderBase.h"

#define _USE_MATH_DEFINES
#include <math.h>


#define LINE_START 0
#define LINE_END 1

class LineCollider_t :public ColliderBase
{
private:

	Location GetMiddlePoint(Location point1, Location point2)const
	{
		Location middle_point;
		middle_point.x = (point1.x + point2.x) / 2;
		middle_point.y = (point1.y + point2.y) / 2;

		return middle_point;
	}
	void Relativize()
	{
		vector[LINE_START].x = vector[LINE_START].x - location.x;
		vector[LINE_START].y = vector[LINE_START].y - location.y;

		vector[LINE_END].x = vector[LINE_END].x - location.x;
		vector[LINE_END].y = vector[LINE_END].y - location.y;
	}
	Location MakeTip(int index)const
	{
		//�����̒[�̐�΍��W���v�Z����
		Location tip;
		tip.x = location.x + vector[index].x;
		tip.y = location.y + vector[index].y;

		return tip;
	}
public:
	LineCollider_t();
	LineCollider_t(Location point1, Location point2);
	~LineCollider_t();

	//�`��
	virtual void Draw()const;

	//�_�Ƃ̓����蔻��
	bool HitDot(Location point)const;

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(const class SphereCollider* sphere_collider)const override;

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const class BoxCollider* box_collider)const override;

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(const class LineCollider_t* line_collider)const override;

	//���̒[�̍��W�̎擾
	Location GetLocation(int i)const;

	//�n�_�A�I�_���W�̐ݒ�
	void SetLocation(Location location, int i);



protected:
	Location vector[2];	//���S������̒[�̍��W�܂ł̃x�N�^�[(0:�n�_,1:�I�_)
};

class LineCollider
{
protected:

	Location location[2];	//���̒[�̍��W(0:�n�_,1:�I�_)
public:

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(class SphereCollider* sphere_collider);

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(class BoxCollider* box_collider);

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(LineCollider* line_collider);

	//���̒[�̍��W�̎擾
	Location GetLocation(int i)const;

	//���S���W�̐ݒ�
	void SetLocation(Location location, int i);

#ifdef _SHOW_COLLISION
	void DrawCollision()const
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawLineAA(location[0].x, location[0].y, location[1].x, location[1].y, 0xE9FF00);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//DrawCircle
	}
#endif
};