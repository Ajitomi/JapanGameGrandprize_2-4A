#pragma once
#include "Define.h"
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
};