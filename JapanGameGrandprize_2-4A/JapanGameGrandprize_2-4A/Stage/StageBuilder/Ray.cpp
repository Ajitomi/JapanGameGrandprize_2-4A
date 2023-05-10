#include "Ray.h"

//------------------------------
// �R���X�g���N�^
//------------------------------
Ray::Ray()
{
	
}

//------------------------------
// �R���X�g���N�^
//------------------------------
Ray::Ray(const Location* location, float shift_x, float shift_y) :base_location(location)
{
	LineCollider::SetLocation(Location{ 0,0 }, LINE_START);
	LineCollider::SetLocation(Location{ 0,100 }, LINE_END);
	Location base_location = *(this->base_location);

	LineCollider::ColliderBase::SetLocation
	(
		base_location - LineCollider::GetVector(LINE_START)
	);

	hit_collider_type = COLLIDER::NONE;
	shift = Location{ shift_x,shift_y };
}

//------------------------------
// �f�X�g���N�^
//------------------------------
Ray::~Ray()
{

}

//--------------------------
// �X�V
//--------------------------
void Ray::Update()
{
	UpdateLocation();
	//�܂��������Ă��邩�m�F���ē������ĂȂ���Ώ���
	for (int i = 0; i < hit_colliders.size(); i++)
	{

		if (HitCheck(hit_colliders[i]) == false)
		{
			hit_colliders.erase(hit_colliders.begin() + i);
		}

	}
	location;
}

//----------------------------------------
// �`��
//----------------------------------------
void Ray::Draw()const
{
#ifdef _DEBUG
	LineCollider::Draw();

	int i = 0;
	for (ColliderBase* hit_collider : hit_colliders )
	{
		DrawFormatString(500, 100 + i*20, 0xFFFF00, "%d", hit_collider->GetColliderType());
		i++;
	}
#endif 
}

//----------------------------------
// �ꏊ�̍X�V
//----------------------------------
void Ray::UpdateLocation()
{
	Location base_location = *(this->base_location);
	LineCollider::ColliderBase::SetLocation
	(
		base_location - LineCollider::GetVector(LINE_START) + shift
	);

}

//-------------------------------------
// �����������̏��� �����������̎�ނ̋L��
//-------------------------------------
void Ray::HitFunction(ColliderBase* collider)
{
	int collider_type = collider->GetColliderType();

	bool is_exist = false;
	for (ColliderBase* hit_collider : hit_colliders)
	{
		if (hit_collider == collider)is_exist = true;
	}
	if (!is_exist)
	{
		hit_colliders.push_back(collider);
	}
}

//----------------------------------------------
// �������Ă���R���_�[��T��
//----------------------------------------------
const ColliderBase* Ray::SearchCollider(COLLIDER collider_type)const
{
	for (ColliderBase* hit_collider : hit_colliders)
	{
		if ((int)collider_type == hit_collider->GetColliderType())
		{
			return hit_collider;
		}
	}

	return nullptr;
}