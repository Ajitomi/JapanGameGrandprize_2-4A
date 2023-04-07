#pragma once
#include "DxLib.h"
#include "Stage/StageBuilder/KeyManager.h"
#include "define.h"
#define _USE_MATH_DEFINES
#include <math.h>

class BoxCollider;
class SphereCollider;
class LineCollider;
class PolyLine;

class ColliderBase
{
public:

	ColliderBase()
	{
		location = { 0,0 };
	}
	ColliderBase(Location location)
	{
		this->location = location;
	}

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
	virtual void SetLocation(Location location)
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

	//SphereCollider�Ƃ̓����蔻��
	virtual bool HitSphere(const class SphereCollider* sphere_collider) const = 0;

	//BoxCollider�Ƃ̓����蔻��
	virtual bool HitBox(const class BoxCollider* box_collider) const = 0;

	//LineCollider�Ƃ̓����蔻��
	virtual bool HitLine(const class LineCollider* line_collider)const = 0;

	virtual ColliderBase* Copy()const = 0;

	virtual  bool HitCheck(ColliderBase* collider)const = 0;

	virtual void Draw()const {}

	const char* GetName() { return class_name; }

protected:

	const char* class_name = "default";

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

	Location location;	//���S���W
};