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
	//������LineCollider�̎n�_���N�_�ɂ��ďo���x�N�g��
	float vec_p[3];

	//�����LineCollider�̎n�_���N�_�ɂ��ďo���x�N�g��
	float vec_m[3];

	//������LineCollider�̃x�N�g��
	vec_p[0] = fabsf((location[0].x * location[1].x) - (location[0].y * location[1].y));

	//������LineCollider�̎n�_�Ƒ����LineCollider�̎n�_�̃x�N�g��
	vec_p[1] = fabsf((line_collider->GetLocation(0).x * location[1].x) - (line_collider->GetLocation(0).x * location[0].y));

	//������LineCollider�̎n�_�Ƒ����LineCollider�̏I�_�̃x�N�g��
	vec_p[2] = fabsf((line_collider->GetLocation(1).x * location[1].x) - (line_collider->GetLocation(1).x * location[0].y));


	//�����LineCollider�̃x�N�g��
	vec_m[0] = fabsf((line_collider->GetLocation(0).x * line_collider->GetLocation(1).x) - (line_collider->GetLocation(0).y * line_collider->GetLocation(1).y));

	//�����LineCollider�̎n�_�Ƒ����LineCollider�̎n�_�̃x�N�g��
	vec_m[1] = fabsf((line_collider->GetLocation(0).x * location[1].x) - (line_collider->GetLocation(0).x * location[0].y));

	//�����LineCollider�̎n�_�Ƒ����LineCollider�̏I�_�̃x�N�g��
	vec_m[2] = fabsf((line_collider->GetLocation(1).x * location[1].x) - (line_collider->GetLocation(1).x * location[0].y));
}