#pragma once
#include"define.h"

#include"Stage/StageBuilder/Debug.h"
#include"DxLib.h"

#include "SphereCollider.h"
#include "LineCollider.h"
#include "ColliderBase.h"

#define BOX_COLLIDER_NAME "BoxCollider"

class BoxCollider : public ColliderBase
{
protected:
	
	Area area; //�͈�
	Area margin_area;	//�����蔻��͈͂̌덷�C��
public:

	BoxCollider();
	BoxCollider(Location location, Area area);
	~BoxCollider();

	virtual void Draw()const;

	//SphereCollider�Ƃ̓����蔻��
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const class BoxCollider* box_collider) const override;

	//LineCollider�Ƃ̓����蔻��
	bool HitLine(const class LineCollider* line_collider) const override;

	ColliderBase* Copy()const override { return new BoxCollider(*this); }

	bool HitCheck(ColliderBase* collider)const;
	
	//���S���W�̎擾
	Location GetLocation()const;

	//���a�̎擾
	Area GetArea()const;

	//���S���W�̐ݒ�
	virtual void SetLocation(Location location);

	//�Q�[���v���C���ɓ����蔻����Ƃ镪�ɂ͕K�v�̂Ȃ�����
	//�c�[����Ń}�E�X�Ƃ̓����蔻����Ƃ邽�߂Ɏg�p���Ă��܂�
#ifdef _STAGE_BUILDER
private:
	SphereCollider spheres[4];
	SphereCollider pivot;
	Location old_pos[4];

public:
	SphereCollider* GetSpheres() { return spheres; }
	SphereCollider* GetPivot() { return &pivot; }
	void UpdatePos();
#endif

};