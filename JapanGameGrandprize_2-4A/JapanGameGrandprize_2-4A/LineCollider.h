#pragma once
#include "Define.h"
#include "Stage/StageBuilder/Debug.h"
#include "ColliderBase.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define LINE_START 0
#define LINE_END 1

class LineCollider :public ColliderBase
{
private:

	//���_��Ԃ�
	Location GetMiddlePoint()const
	{
		Location middle_point;
		middle_point.x = (vector[LINE_START].x + vector[LINE_END].x) / 2;
		middle_point.y = (vector[LINE_START].y + vector[LINE_END].y) / 2;

		return middle_point;
	}

	//���W�𒆐S���W����̃x�N�^�[�ɑ��Ή�����
	void Relativize()
	{
		vector[LINE_START].x = vector[LINE_START].x - location.x;
		vector[LINE_START].y = vector[LINE_START].y - location.y;

		vector[LINE_END].x = vector[LINE_END].x - location.x;
		vector[LINE_END].y = vector[LINE_END].y - location.y;
	}

	//�����̒[�̐�΍��W��Ԃ�
	Location MakeTip(int index)const
	{
		//�����̒[�̐�΍��W���v�Z����
		Location tip;
		tip.x = location.x + vector[index].x;
		tip.y = location.y + vector[index].y;

		return tip;
	}


public:
	LineCollider();
	LineCollider(Location point1, Location point2);
	~LineCollider();

	//�`��
	virtual void Draw()const;

	//�_�Ƃ̓����蔻��
	bool HitDot(Location point)const;

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(const class SphereCollider* sphere_collider)const override;

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const class BoxCollider* box_collider)const override;

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(const class LineCollider* line_collider)const override;

	ColliderBase* Copy()const override { return new LineCollider(*this); }

	//���̒[�̍��W�̎擾
	Location GetLocation(int i)const;

	//�n�_�A�I�_���W�̐ݒ�
	void SetLocation(Location location, int i);


	//������Ίp���Ƃ�����`�̍���̍��W��Ԃ�
	Location GetMin()const
	{
		Location vector_min = {};
		float x;
		float y;

		if (GetLocation(LINE_START).x < GetLocation(LINE_END).x)
		{
			x = GetLocation(LINE_START).x;
		}
		else
		{
			x = GetLocation(LINE_END).x;
		}

		if (GetLocation(LINE_START).y < GetLocation(LINE_END).y)
		{
			y = GetLocation(LINE_START).y;
		}
		else
		{
			y = GetLocation(LINE_END).y;
		}

		vector_min = { x,y };

		return vector_min;
	}

	//������Ίp���Ƃ�����`�̉E���̍��W��Ԃ�
	Location GetMax()const
	{
		Location vector_max{};
		float x;
		float y;

		if (GetLocation(LINE_START).x > GetLocation(LINE_END).x)
		{
			x = GetLocation(LINE_START).x;
		}
		else
		{
			x = GetLocation(LINE_END).x;
		}

		if (GetLocation(LINE_START).y > GetLocation(LINE_END).y)
		{
			y = GetLocation(LINE_START).y;
		}
		else
		{
			y = GetLocation(LINE_END).y;
		}

		vector_max = { x,y };

		return vector_max;
	}

protected:

	Location vector[2];	//���S������̒[�̍��W�܂ł̃x�N�^�[(0:�n�_,1:�I�_)
};