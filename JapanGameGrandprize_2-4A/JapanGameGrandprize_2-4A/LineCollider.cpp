#define _USE_MATH_DEFINES
#include<math.h>
#include "LineCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool LineCollider::HitSphere(class SphereCollider* sphere_collider)
{

	bool ret = false; //�Ԃ�l

	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float unit_vector;	//�P�ʃx�N�g��
	float shortest_distance; //�����Ɖ~�̍ŒZ�̋���

	float inner_product[2]; //����(0:x,1:y)
	float center_distance[2]; //�~�̒��S�Ƃ̋���(0:�����̎n�_�@1:�����̏I�_)

	//������LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
	vector_x[0] = location[1].x - location[0].x;
	vector_y[0] = location[1].y - location[0].y;

	//������LineCollider�̎n�_��phereCollider�̒��S�Ƃ̃x�N�g���̌v�Z
	vector_x[1] = sphere_collider->GetLocation().x - location[0].x;
	vector_y[1] = sphere_collider->GetLocation().y - location[0].y;

	//������LineCollider�̏I�_��SphereCollider�̒��S�Ƃ̃x�N�g���̌v�Z
	vector_x[2] = sphere_collider->GetLocation().x - location[1].x;
	vector_y[2] = sphere_collider->GetLocation().y - location[1].y;

	//�P�ʃx�N�g���̌v�Z
	unit_vector = sqrt(pow(vector_x[0], 2) + pow(vector_y[0], 2));

	//�ŒZ�����̌v�Z
	shortest_distance = (vector_x[1] * (vector_x[0] / unit_vector)) - (vector_y[1] * (vector_y[0] / unit_vector));

	if (fabsf(shortest_distance) <= sphere_collider->GetRadius())
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

		if ((inner_product[0] * inner_product[1] <= 0.0f) || (center_distance[0] < sphere_collider->GetRadius()) || 
			(center_distance[1] < sphere_collider->GetRadius()))
		{
			ret = true;
		}
	}

	return ret;
}

bool LineCollider::HitBox(class BoxCollider* box_collider)
{
	bool ret = false; //�Ԃ�l

	return ret;
}

bool LineCollider::HitLine(LineCollider* line_collider)
{

	bool ret = false; //�Ԃ�l

	/*������LineCollider�̎n�_���N�_�ɂ��ďo���x�N�g��*/
	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float outer_product[2]; //�O��

	//������LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
	vector_x[0] = location[1].x - location[0].x;
	vector_y[0] = location[1].y - location[0].y;

	//������LineCollider�̎n�_�Ƒ����LineCollider�̎n�_�Ƃ̃x�N�g���̌v�Z
	vector_x[1] = line_collider->GetLocation(0).x - location[0].x;
	vector_y[1] = line_collider->GetLocation(0).y - location[0].y;

	//������LineCollider�̎n�_�Ƒ����LineCollider�̏I�_�Ƃ̃x�N�g���̌v�Z
	vector_x[2] = line_collider->GetLocation(1).x - location[0].x;
	vector_y[2] = line_collider->GetLocation(1).y - location[0].y;

	//�O�ς̌v�Z
	for (int i = 0; i < 2; i++)
	{
		outer_product[i] = (vector_x[0] * vector_y[i + 1]) - (vector_x[i + 1] * vector_y[0]);
	}

	//�����蔻��̔��f
	if (outer_product[0] * outer_product[1] <= 0.0f)
	{
		ret = true;
	}

	return ret;
}