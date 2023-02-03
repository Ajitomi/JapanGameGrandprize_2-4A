#include "BoxCollider.h"
#include"SphereCollider.h"
#define _USE_MATH_DEFINES
#include<math.h>


//SphereCollider�Ƃ̓����蔻��
bool BoxCollider::HitSphere(class SphereCollider* sphere_collider)
{
	bool ret = false;//�Ԃ�l
	float rad; //2�_�̊p�x
	float sphere_x; //�~�̍��W(x)
	float sphere_y; //�~�̍��W(y)

	//�p�x�̌v�Z
	rad = atan2f(sphere_collider->GetLocation().y - location.y, sphere_collider->GetLocation().x - location.x);

	//���W�̌v�Z
	sphere_x = sphere_collider->GetLocation().x + (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y + (sphere_collider->GetRadius() * sinf(rad));

	//�����̓����蔻��͈̔�
	float mx1 = location.x - (area.width / 2);
	float my1 = location.y - (area.height / 2);
	float mx2 = mx1 - area.width;
	float my2 = my1 - area.height;


	if ((mx1 > sphere_x) && (mx2 < sphere_x) && (my1 > sphere_y) && (my2 < sphere_y)) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

//BoxCollider�Ƃ̓����蔻��
bool BoxCollider::HitBox(BoxCollider* box_collider)
{
	bool ret = false; //�Ԃ�l

	//�����̓����蔻��͈̔�
	//float mx1 = location.x - (erea.width / 2);
	//float my1 = location.y - (erea.height / 2);
	float mx1 = location.x;
	float my1 = location.y;
	float mx2 = mx1 + area.width;
	float my2 = my1 + area.height;

	//����̓����蔻��͈̔�
	//float px1 = box_collider.GetLocation().x - (box_collider.GetErea().width / 2);
	//float py1 = box_collider.GetLocation().x - (box_collider.GetErea().height / 2);
	float px1 = box_collider->GetLocation().x;
	float py1 = box_collider->GetLocation().y;
	float px2 = px1 + box_collider->GetArea().width;
	float py2 = py1 + box_collider->GetArea().height;

	if ((mx1 < px2) && (px1 < mx2) && (my1 < py2) && (py1 < my2)) //�����蔻��
	{
		ret = true;
	}
	return ret;
}

//���S���W�̎擾
Location BoxCollider::GetLocation()const
{
	return location;
}

//���a�̎擾
Area BoxCollider::GetArea()const
{
	return area;
}

//���S���W�̐ݒ�
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}