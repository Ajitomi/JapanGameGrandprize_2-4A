#include "ObjectBase.h"
#include "../../BoxCollider.h"

//--------------------------------
// �R���X�g���N�^
//--------------------------------
ObjectBase::ObjectBase()
{
	pivot = { 640,360 };
}

//--------------------------------
// �R���X�g���N�^
//--------------------------------
ObjectBase::ObjectBase(Location pivot)
{
	this->pivot = pivot;
	image = LoadGraph("images/Stage/yuka_1.png");

	collider =  new BoxCollider({ 640,360 }, { 100,100 });

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
	DrawRotaGraphF(pivot.x, pivot.y, 1.0, 0, image, TRUE, is_reverse);

	collider->Draw();
}

//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------
