#include "BoxCollider.h"
#include "SphereCollider.h"
#include "LineCollider.h"
#include "CameraWork.h"
#include <math.h>

#define _USE_MATH_DEFINES

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
 BoxCollider::BoxCollider()
{

}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
 BoxCollider::BoxCollider(Location location, Area area):ColliderBase(location)
 {
	 this->area = area;

#ifdef _STAGE_BUILDER

	 pivot = new SphereCollider(location);

	 spheres = new SphereCollider * [4];

	 spheres[0] = new SphereCollider(
		 {
			 location.x - area.width / 2,location.y - area.height / 2
		 }
	 );

	 spheres[1] = new SphereCollider(
		 {
			 location.x + area.width / 2,location.y - area.height / 2
		 }
	 );

	 spheres[2] = new SphereCollider(
		 {
			 location.x - area.width / 2,location.y + area.height / 2
		 }
	 );

	 spheres[3] = new SphereCollider(
		 {
			 location.x + area.width / 2,location.y + area.height / 2
		 }
	 );

#endif
 }

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
 BoxCollider::~BoxCollider()
 {
#ifdef _STAGE_BUILDER
	 delete[] spheres;
	 delete pivot;
#endif
 }

 //----------------------------------
 // �`��
 //----------------------------------
 void BoxCollider::Draw()const
 {
	 DrawBoxAA(location.x - area.width / 2 - CameraWork::GetCamera().x, 
		 location.y - area.height / 2 - CameraWork::GetCamera().y,
		 location.x + area.width / 2 - CameraWork::GetCamera().x,
		 location.y + area.height / 2 - CameraWork::GetCamera().y
		 , 0xff00ff, FALSE);

#ifdef _STAGE_BUILDER

	 for (int i = 0; i < 4; i++)
	 {
		 if (spheres[i] != nullptr)
		 {
			spheres[i]->Draw();
		 }
	 }
	 if (pivot != nullptr)
	 {
		 pivot->Draw();
	 }

#endif
 }

//-----------------------------------
// SphereCollider�Ƃ̓����蔻��
//-----------------------------------
bool BoxCollider::HitSphere(const class SphereCollider* sphere_collider) const
{

	bool ret = false;//�Ԃ�l
	float rad; //2�_�̊p�x
	float sphere_x; //�~�̍��W(x)
	float sphere_y; //�~�̍��W(y)

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//�p�x�̌v�Z
	rad = atan2f(sphere_collider->GetLocation().y - location.y,
			      sphere_collider->GetLocation().x - location.x);

	//���W�̌v�Z
	sphere_x = sphere_collider->GetLocation().x 
		        + (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y 
		        + (sphere_collider->GetRadius() * sinf(rad));

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	if ((my_x[0] <= sphere_x) && (sphere_x <= my_x[1]) 
		    && (my_y[0] <= sphere_y) && (sphere_y <= my_y[1])) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// BoxCollider�Ƃ̓����蔻��
//-----------------------------------
bool BoxCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //�Ԃ�l

	//�����蔻��͈͂̌덷�C��
	Area margin_area = { box_collider->margin_area.height, box_collider->margin_area.width };

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
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] <= sub_x[1] + margin_area.width) && (sub_x[0] + margin_area.width <= my_x[1])
		    && (my_y[0] <= sub_y[1] + margin_area.height) && (sub_y[0] +  margin_area.height <= my_y[1])) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// LineCollider�Ƃ̓����蔻��
//-----------------------------------
bool BoxCollider::HitLine(const class LineCollider* line_collider) const
{
	bool is_hit = false;
	bool box_ishit = false;
	float sign = 0;

	Location vertex[4] =
	{
		//�l��
		{GetLocation().x - GetArea().width / 2,
		GetLocation().y - GetArea().height / 2 },

		{GetLocation().x + GetArea().width / 2,
		GetLocation().y - GetArea().height / 2 },

		{GetLocation().x - GetArea().width / 2,
		GetLocation().y + GetArea().height / 2 },

		{GetLocation().x + GetArea().width / 2,
		GetLocation().y + GetArea().height / 2},

	};

	for (int i = 0; i < 4; i++)
	{
		if ((line_collider->GetMin() <= vertex[i]) && 
			vertex[i] <= line_collider->GetMax())
		{
			box_ishit = true;
		}
	}
	if (box_ishit == false)return false; //�������͂��l�p�`�ɂ��瓖�����ĂȂ�


	for (int i = 0; i < 4; i++)
	{
		float closs_product = 0;

		Location vector1 =
			line_collider->GetLocation(LINE_START) -
			line_collider->GetLocation(LINE_END);
		Location vector2 =
			vertex[i] - line_collider->GetLocation(LINE_END);

		closs_product = (vector1.x * vector2.y) - (vector1.y * vector2.x);
		if (closs_product == 0)return true;	//0�Ȃ���ƒ��_���d�Ȃ��Ă���̂œ�����

		if (i == 0)
		{
			sign = closs_product;
		}
		else
		{
			if ((sign * closs_product) < 0)
			{
				is_hit = true;
				break;
			}
		}
	}

	return is_hit;
}

//-----------------------------------
// ���S���W�̎擾
//-----------------------------------
Location BoxCollider::GetLocation()const
{

	return location;
}

//-----------------------------------
// ���a�̎擾
//-----------------------------------
Area BoxCollider::GetArea()const
{

	return area;
}

//-----------------------------------
// ���S���W�̐ݒ�
//-----------------------------------
void BoxCollider::SetLocation(Location location)
{

#ifdef _STAGE_BUILDER

	Location distance = location - this->location;

	pivot->SetLocation(location);
	for (int i = 0; i < 4; i++)
	{
		spheres[i]->SetLocation(spheres[i]->GetLocation() + distance);
	}

#endif

	this->location = location;

}

#ifdef _STAGE_BUILDER

//---------------------------------------
// ���W�̍X�V �l�p�`�ɂȂ�悤�ɍ��킹��
//---------------------------------------
void BoxCollider::UpdatePos()
{
	for (int i = 0; i < 4; i++)
	{
		if (spheres[i]->GetLocation() != old_pos[i])
		{
			 //3����Y�����������ƑΊp�̓Y�����ɂȂ�B
			area.height = fabsf(spheres[3 - i]->GetLocation().y -
				spheres[i]->GetLocation().y);

			area.width = fabsf(spheres[3 - i]->GetLocation().x -
				spheres[i]->GetLocation().x);

			pivot->SetLocation(
				{
					(spheres[3 - i]->GetLocation() +
					spheres[i]->GetLocation()) / Location{2,2}
				}
			);


			break;
		}
	}

	SetLocation(pivot->GetLocation());

	spheres[0]->SetLocation
	({ location.x - area.width / 2,location.y - area.height / 2 });

	spheres[1]->SetLocation
	({ location.x + area.width / 2,location.y - area.height / 2 });

	spheres[2]->SetLocation
	({ location.x - area.width / 2,location.y + area.height / 2 });

	spheres[3]->SetLocation
	({ location.x + area.width / 2,location.y + area.height / 2 });

	for (int i = 0; i < 4; i++)
	{
		old_pos[i] = spheres[i]->GetLocation();
	}
}

#endif