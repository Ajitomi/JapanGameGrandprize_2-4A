#include "Ray.h"

//------------------------------
// �R���X�g���N�^
//------------------------------
Ray::Ray()
{
	int a=4;
	const int b = 5;
	int c = a + b;

}

//------------------------------
// �R���X�g���N�^
//------------------------------
Ray::Ray(const Location* location):base_location(location)
{
	LineCollider::SetLocation(Location{ 0,0 }, LINE_START);
	LineCollider::SetLocation(Location{ 0,100 }, LINE_END);

	LineCollider::ColliderBase::SetLocation
	(
		*base_location - LineCollider::GetVector(LINE_START)
		)
}

//------------------------------
// �f�X�g���N�^
//------------------------------
Ray::~Ray()
{

}