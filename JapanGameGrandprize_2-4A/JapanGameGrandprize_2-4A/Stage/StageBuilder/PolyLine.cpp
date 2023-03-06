#include "PolyLine.h"
#include "DxLib.h"

//-------------------------------------
// �R���X�g���N�^ �����F�_�̍��W�Ɛ�
//-------------------------------------
PolyLine::PolyLine(Location bend_points[], unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		this->bend_points.push_back(new SphereCollider(bend_points[i]));
	}
	for (int i = 0; i < size - 1; i++)
	{
		lines.push_back(new LineCollider_t(bend_points[i], bend_points[i + 1]));
	}
}

//---------------------------------
// �f�X�g���N�^
//---------------------------------
PolyLine::~PolyLine()
{

}


//---------------------------------
// �X�V
//---------------------------------
void PolyLine::Update()
{
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->SetLocation(bend_points[i]->GetLocation(), LINE_START);
		lines[i]->SetLocation(bend_points[i + 1]->GetLocation(), LINE_END);
	}
}

//---------------------------------
// �`��
//---------------------------------


//---------------------------------
// 
//---------------------------------


//---------------------------------
// 
//---------------------------------


//---------------------------------
// 
//---------------------------------


#ifdef _SHOW_COLLISION
void PolyLine::DrawCollision()const
{
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->DrawCollision();
	}
	for (int i = 0; i < bend_points.size(); i++)
	{
		SphereCollider* it = bend_points[i];
		DrawCircleAA(it->GetLocation().x, it->GetLocation().y, 5, 10,
			0x666666);
	}
}
#endif
