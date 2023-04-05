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
	this->pivot = new SphereCollider(pivot);
	image = LoadGraph("images/Stage/yuka_1.png");
	

	p_collider = dynamic_cast<BoxCollider*>(p_collider);
	if (p_collider)
	{
		collider = new BoxCollider(*dynamic_cast<BoxCollider*>(p_collider));
	}

	p_collider = dynamic_cast<SphereCollider*>(p_collider);
	if (p_collider)
	{
		collider = new SphereCollider(*dynamic_cast<SphereCollider*>(p_collider));
	}

	p_collider = dynamic_cast<LineCollider*>(p_collider);
	if (p_collider)
	{
		collider = new LineCollider(*dynamic_cast<LineCollider*>(p_collider));
	}

	p_collider = dynamic_cast<PolyLine*>(p_collider);
	if (p_collider)
	{
		collider = new PolyLine(*dynamic_cast<PolyLine*>(p_collider));
	}


	vector = collider->GetLocation() - pivot;
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
	Location draw_pos = pivot->GetLocation() + vector - CameraWork::GetCamera();

	DrawRotaGraphF(draw_pos.x,draw_pos.y,1.0, 0, image, TRUE, is_reverse);

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
	collider->SetLocation(pivot->GetLocation() + vector);
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
