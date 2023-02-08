#define _USE_MATH_DEFINES
#include<math.h>
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "LineCollider.h"



//SphereCollider�Ƃ̓����蔻��
bool BoxCollider::HitSphere(class SphereCollider* sphere_collider)
{
	bool ret = false;//�Ԃ�l
	float rad; //2�_�̊p�x
	float sphere_x; //�~�̍��W(x)
	float sphere_y; //�~�̍��W(y)

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//�p�x�̌v�Z
	rad = atan2f(sphere_collider->GetLocation().y - location.y, sphere_collider->GetLocation().x - location.x);

	//���W�̌v�Z
	sphere_x = sphere_collider->GetLocation().x + (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y + (sphere_collider->GetRadius() * sinf(rad));

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] - area.width;
	my_y[1] = my_y[0] - area.height;


	if ((sphere_x < my_x[0]) && (my_x[1] < sphere_x) && (sphere_y < my_y[0]) && (my_y[1] < sphere_y)) //�����蔻��
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
	float my_x[2];
	float my_y[2];

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().x - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] < sub_x[1]) && (sub_x[0] < my_x[1]) && (my_y[0] < sub_y[1]) && (sub_y[0] < my_y[1])) //�����蔻��
	{
		ret = true;
	}
	return ret;
}

//LineCollider�Ƃ̓����蔻��
bool BoxCollider::HitLine(LineCollider* line_collider)
{
	bool ret = false; //�Ԃ�l

	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float outer_product[4]; //�O��

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];

	bool sign = false; //�ŏ��̊O�ς̕���(true:���̐��Afalse:���̐�)

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = sub_x[0] + area.width;
	my_y[1] = sub_y[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	if (line_collider->GetLocation(0).x <= line_collider->GetLocation(1).x)
	{
		sub_x[0] = line_collider->GetLocation(0).x;
		sub_x[1] = line_collider->GetLocation(1).x;

	}
	else
	{
		sub_x[0] = line_collider->GetLocation(1).x;
		sub_x[1] = line_collider->GetLocation(0).x;
	}

	if (line_collider->GetLocation(0).y <= line_collider->GetLocation(1).y)
	{
		sub_y[0] = line_collider->GetLocation(0).y;
		sub_y[1] = line_collider->GetLocation(1).y;
	}
	else
	{
		sub_y[0] = line_collider->GetLocation(1).y;
		sub_y[1] = line_collider->GetLocation(0).y;
	}


	if ((my_x[0] < sub_x[1]) && (my_x[1] < sub_x[1]) && (my_y[0] < sub_y[1]) && (sub_y[0] < my_y[1]))
	{
		//LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
		vector_x[0] = line_collider->GetLocation(1).x - line_collider->GetLocation(0).x;
		vector_y[0] = line_collider->GetLocation(1).y - line_collider->GetLocation(0).y;

		//������LineCollider�̎n�_�ƍ���̊p�Ƃ̃x�N�g��
		vector_x[1] = location.x - line_collider->GetLocation(0).x;
		vector_y[1] = location.y - line_collider->GetLocation(0).y;

		//������LineCollider�̎n�_�ƉE���̊p�Ƃ̃x�N�g��
		vector_x[2] = (location.x + area.width) - line_collider->GetLocation(0).x;
		vector_y[2] = (location.y + area.height) - line_collider->GetLocation(0).y;

		//�e���_�ƊO�ς̌v�Z
		for (int i = 0, n = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				outer_product[n++] = (vector_x[0] * vector_y[i]) - (vector_y[0] * vector_x[j]);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (outer_product[i] == 0) //�O�ς̒l��0�Ȃ瓖�����Ă���
			{
				ret = true;
				break;
			}

			if (i == 0)
			{
				//�E��̊p�Ƃ̊O�ς̕����̎擾
				sign = signbit(outer_product[0]);
			}
			else
			{

				if (sign != signbit(outer_product[i]))	//����̊p�Ƃ̊O�ς̕�����������瓖�����Ă���
				{
					ret = true;
					break;
				}
			}
		}
	}
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