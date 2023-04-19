#include "ObjectBase.h"
#include "../../BoxCollider.h"
#include "../CameraWork.h"

//--------------------------------
// �R���X�g���N�^
//--------------------------------
ObjectBase::ObjectBase()
{
	pivot = new SphereCollider({ 640,360 });
}

//--------------------------------
// �R���X�g���N�^
//--------------------------------
ObjectBase::ObjectBase(Location pivot, ColliderBase* p_collider)
{
	ColliderBase* base;
	this->pivot = new SphereCollider(pivot);
	image = LoadGraph("images/Stage/yuka_1.png");
	
	int class_type = p_collider->GetName();
	switch (class_type)
	{
	case (int)COLLIDER::DEFAULT:
		collider = new BoxCollider(*static_cast<BoxCollider*>(p_collider));
		break;
	}

	//TODO:�������� dynamic_cast��static_cast�ɒ���

	base = dynamic_cast<BoxCollider*>(p_collider);
	if (base)
	{
		collider = new BoxCollider(*dynamic_cast<BoxCollider*>(p_collider));
	}

	base = dynamic_cast<SphereCollider*>(p_collider);
	if (base)
	{
		collider = new SphereCollider(*dynamic_cast<SphereCollider*>(p_collider));
	}

	base = dynamic_cast<LineCollider*>(p_collider);
	if (base)
	{
		collider = new LineCollider(*dynamic_cast<LineCollider*>(p_collider));
	}

	base = dynamic_cast<PolyLine*>(p_collider);
	if (base)
	{
		collider = new PolyLine(*dynamic_cast<PolyLine*>(p_collider));
	}


	vector = collider->GetLocation() - pivot;
	old_location = collider->GetLocation();
	is_reverse = FALSE;
	
}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
ObjectBase::~ObjectBase()
{
	
}

//--------------------------------
// �`��
//--------------------------------
void ObjectBase::Draw()const
{
	Location draw_pos = pivot->GetLocation() - CameraWork::GetCamera();

	DrawRotaGraphF(draw_pos.x,draw_pos.y,1.0, 0, image, TRUE, is_reverse);

	DrawLineAA(pivot->GetLocation().x - CameraWork::GetCamera().x, pivot->GetLocation().y - CameraWork::GetCamera().y,
		collider->GetLocation().x - CameraWork::GetCamera().x, collider->GetLocation().y - CameraWork::GetCamera().y, 0xFFFF00, 3);

#ifdef _STAGE_BUILDER
	pivot->Draw();
	collider->Draw();
#endif
}

//--------------------------------
// �����蔻��N���X�̏ꏊ�̍X�V
//--------------------------------
void ObjectBase::UpdateColliderPos()
{
	if (old_location != collider->GetLocation())
	{
		vector = collider->GetLocation() - pivot->GetLocation();
		old_location = collider->GetLocation();
	}
	else
	{
		collider->SetLocation(pivot->GetLocation() + vector);
		old_location = collider->GetLocation();
	}
}

//--------------------------------
// �����蔻��N���X�̃L���X�g
//--------------------------------
void ObjectBase::ColliderCast(ColliderBase* p_collider)
{

}

//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------
