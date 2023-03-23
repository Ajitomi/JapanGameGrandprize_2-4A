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

	//2�̃x�N�g���̂Ȃ��p���s�p���ǂ��������߂�
	bool CheckIsAcute(Location vector1, Location vector2)const
	{
		bool is_acute = false;

		float vec_a = powf(powf(vector1.x, 2.0) + powf(vector1.y, 2.0), 0.5);
		float vec_b = powf(powf(vector2.x, 2.0) + powf(vector2.y, 2.0), 0.5);

		float inner_product = vector1.x * vector2.x + vector1.y * vector2.y;

		if (inner_product >= 0)
		{
			is_acute = true;
		}

		return is_acute;
	}

	//�󂯎�����x�N�^�[�̃X�J����Ԃ�
	float MakeScalar(Location vector)const
	{
		float scalar;

		scalar = powf((vector.x * vector.x) + (vector.y * vector.y), 0.5);

		return scalar;
	}

	//�����P��������Q�ɑ΂���O�ς�Ԃ�
	float MakeCrossProduct(Location vector1, Location vector2)const
	{
		float cross_product;

		cross_product = (vector1.x * vector2.y) - (vector1.y * vector2.x);

		return cross_product;
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