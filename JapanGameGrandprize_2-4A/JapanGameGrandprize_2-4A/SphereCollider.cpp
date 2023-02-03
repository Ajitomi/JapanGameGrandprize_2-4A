#define _USE_MATH_DEFINES
#include<math.h>
#include "BoxCollider.h"
#include"SphereCollider.h"


bool SphereCollider::HitSphere(SphereCollider* sphere_collider)
{
	bool ret = false;//�Ԃ�l
	float distance;	//���S���W�̋���

	//���S���W�̋����̌v�Z
	distance = sqrtf(powf(sphere_collider->GetLocation().x - location.x, 2) + powf(sphere_collider->GetLocation().y - location.y, 2));

	if (distance < radius + sphere_collider->GetRadius()) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitBox(class BoxCollider* box_collider)
{
	bool ret = false; //�Ԃ�l
	float rad; //2�_�̊p�x
	float sphere_x; //�~�̍��W(x)
	float sphere_y; //�~�̍��W(y)

	//�p�x�̌v�Z
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//���W�̌v�Z
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y - (radius * sinf(rad));

	//�����̓����蔻��͈̔�
	//float px1 = location.x - (box_collider.GetErea().width / 2);
	//float py1 = location.y - (box_collider.GetErea().height / 2);
	float px1 = box_collider->GetLocation().x;
	float py1 = box_collider->GetLocation().y;
	float px2 = px1 + box_collider->GetArea().width;
	float py2 = py1 + box_collider->GetArea().height;


	if ((px1 < sphere_x) && (sphere_x < px2) && (py1 < sphere_y) && (sphere_y < py2)) //�����蔻��
	{
		ret = true;
	}

	return ret;
}
