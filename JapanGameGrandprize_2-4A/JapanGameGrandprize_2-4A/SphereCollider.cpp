#include "SphereCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include <math.h>

#define _USE_MATH_DEFINES

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

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];

	//�p�x�̌v�Z
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//���W�̌v�Z
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y - (radius * sinf(rad));

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;


	if ((sub_x[0] < sphere_x) && (sphere_x < sub_x[1]) && (sub_y[0] < sphere_y) && (sphere_y < sub_y[1])) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitLine(class LineCollider* line_collider)
{
	bool ret = false; //�Ԃ�l

	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float unit_vector;	//�P�ʃx�N�g��
	float shortest_distance; //�����Ɖ~�̍ŒZ�̋���

	float inner_product[2]; //����(0:x,1:y)
	float center_distance[2]; //�~�̒��S�Ƃ̋���(0:�����̎n�_�@1:�����̏I�_)

	//LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
	vector_x[0] = line_collider->GetLocation(1).x - line_collider->GetLocation(0).x;
	vector_y[0] = line_collider->GetLocation(1).y - line_collider->GetLocation(0).y;

	//LineCollider�̎n�_��phereCollider�̒��S�Ƃ̃x�N�g���̌v�Z
	vector_x[1] = location.x - line_collider->GetLocation(0).x;
	vector_y[1] = location.y - line_collider->GetLocation(0).y;

	//LineCollider�̏I�_��SphereCollider�̒��S�Ƃ̃x�N�g���̌v�Z
	vector_x[2] = location.x - line_collider->GetLocation(1).x;
	vector_y[2] = location.y - line_collider->GetLocation(1).y;

	//�P�ʃx�N�g���̌v�Z
	unit_vector = sqrt(pow(vector_x[0], 2) + pow(vector_y[0], 2));

	//�ŒZ�����̌v�Z
	shortest_distance = (vector_x[1] * (vector_x[0] / unit_vector)) - (vector_y[1] * (vector_y[0] / unit_vector));

	if (fabsf(shortest_distance) <= radius)
	{
		//���ς̌v�Z
		for (int i = 0; i < 2; i++)
		{
			inner_product[i] = (vector_x[i + 1] * vector_x[0]) - (vector_y[i + 1] * vector_y[0]);
		}
		//�~�̒��S�Ƃ̋����̌v�Z
		for (int i = 0; i < 2; i++)
		{
			center_distance[i] = sqrt(pow(vector_x[i + 1], 2) + pow(vector_y[i + 1], 2));
		}

		if ((inner_product[0] * inner_product[1] <= 0.0f) || (center_distance[0] < radius) ||
			(center_distance[1] < radius))
		{
			ret = true;
		}
	}

	return ret;
}