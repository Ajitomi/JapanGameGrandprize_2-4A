#pragma once
#include "Define.h"
#include "Stage/StageBuilder/StageBuilder.h"

#include <math.h>

#define _USE_MATH_DEFINES

#define LINE_START 0
#define LINE_END 1

class LineCollider2
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
		vector[0].x = vector[0].x - location.x;
		vector[0].y = vector[0].y - location.y;

		vector[1].x = vector[1].x - location.x;
		vector[1].y = vector[1].y - location.y;
	}
	Location MakeTip(int index)const
	{//�����̒[�̐�΍��W���v�Z����
		Location tip;
		tip.x = location.x + vector[index].x;
		tip.y = location.y + vector[index].y;

		return tip;
	}
protected:
	Location vector[2];	//���S������̒[�̍��W�܂ł̃x�N�^�[(0:�n�_,1:�I�_)
	Location location;	//���S���W

public:
	LineCollider2();
	LineCollider2(Location point1, Location point2);
	~LineCollider2();

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(class SphereCollider* sphere_collider)const;

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(class BoxCollider* box_collider)const;

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(LineCollider2* line_collider)const;

	//���̒[�̍��W�̎擾
	Location GetLocation(int i)const;

	//�n�_�A�I�_���W�̐ݒ���W�̐ݒ�
	void SetLocation(Location location, int i);

	//���ۉ�����\��̊֐�������
	//���S���W�̎擾
	Location GetLocation()const
	{
		return location;
	}
	//���S���W�̈ړ�
	void MoveLocation()
	{
		const float scalar = 5;
		if (KeyManager::OnKeyClicked(KEY_INPUT_W) || KeyManager::OnKeyClicked(KEY_INPUT_UP))
		{
			location.y -= scalar;
		}

		if (KeyManager::OnKeyClicked(KEY_INPUT_S) || KeyManager::OnKeyClicked(KEY_INPUT_DOWN))
		{
			location.y += scalar;
		}
		
		if (KeyManager::OnKeyClicked(KEY_INPUT_A) || KeyManager::OnKeyClicked(KEY_INPUT_LEFT))
		{
			location.x -= scalar;
		}
		
		if (KeyManager::OnKeyClicked(KEY_INPUT_D) || KeyManager::OnKeyClicked(KEY_INPUT_RIGHT))
		{
			location.x += scalar;
		}

	}
	//���S���W�̐ݒ�
	void SetLocation(Location location)
	{
		const float distance_limit = 700.f;
		Location distance;
		distance.x = this->location.x - location.x;
		distance.y = this->location.y - location.y;
		if (powf(distance.x, 2) + powf(distance.y, 2) < powf(distance_limit, 2))
		{
			this->location = location;
		}
	}

#ifdef _SHOW_COLLISION
	void DrawCollision()const
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawLineAA(GetLocation(LINE_START).x, GetLocation(LINE_START).y,
			GetLocation(LINE_END).x, GetLocation(LINE_END).y,0xE9FF00,3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//DrawCircle
	}
#endif
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