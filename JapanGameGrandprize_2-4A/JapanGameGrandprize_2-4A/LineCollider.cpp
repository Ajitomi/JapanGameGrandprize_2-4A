#define _USE_MATH_DEFINES
#include<math.h>
#include "LineCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool LineCollider::HitSphere(class SphereCollider* sphere_collider)
{

}

bool LineCollider::HitBox(class BoxCollider* box_collider)
{

}

bool LineCollider::HitLine(LineCollider* line_collider)
{

	bool ret = false; //�Ԃ�l

	/*������LineCollider�̎n�_���N�_�ɂ��ďo���x�N�g��*/
	float vec_x[3]; //X���W�̃x�N�g��
	float vec_y[3]; //Y���W�̃x�N�g��

	float outer_product[2]; //�O��

	//������LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
	vec_x[0] = location[1].x - location[0].x;
	vec_y[0] = location[1].y - location[0].y;

	//������LineCollider�̎n�_�Ƒ����LineCollider�̎n�_�Ƃ̃x�N�g���̌v�Z
	vec_x[1] = line_collider->GetLocation(0).x - location[0].x;
	vec_y[1] = line_collider->GetLocation(0).y - location[0].y;

	//������LineCollider�̎n�_�Ƒ����LineCollider�̏I�_�Ƃ̃x�N�g���̌v�Z
	vec_x[2] = line_collider->GetLocation(1).x - location[0].x;
	vec_y[2] = line_collider->GetLocation(1).y - location[0].y;

	//�O�ς̌v�Z
	for (int i = 0; i < 2; i++)
	{
		outer_product[i] = (vec_x[0] * vec_y[i + 1]) - (vec_x[i + 1] * vec_y[0]);
	}

	//�����蔻��̔��f
	if (outer_product[0] * outer_product[1] <= 0.0f)
	{
		ret = true;
	}

	return ret;
}