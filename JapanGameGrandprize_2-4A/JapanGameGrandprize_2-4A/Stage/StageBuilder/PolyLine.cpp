#include "PolyLine.h"
#include "DxLib.h"

//-------------------------------------
// �R���X�g���N�^ 
//-------------------------------------
PolyLine::PolyLine()
{

}

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
		lines.push_back(new LineCollider(bend_points[i], bend_points[i + 1]));
	}
}

//-------------------------------------
// �R���X�g���N�^ �����F�~�̃x�N�^�[�z��
//-------------------------------------
PolyLine::PolyLine(const vector<SphereCollider*> spheres)
{
	for (int i = 0; i < spheres.size(); i++)
	{
		bend_points.push_back(new SphereCollider(*spheres[i]));
	}

	for (int i = 0; i < spheres.size() - 1; i++)
	{
		lines.push_back(new LineCollider(
			spheres[i]->GetLocation(), spheres[i + 1]->GetLocation()
		));
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

//-------------------------------------
// �`��
//-------------------------------------
void PolyLine::Draw()const
{
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->Draw();
	}
	for (int i = 0; i < bend_points.size(); i++)
	{
		bend_points[i]->Draw();
	}
}

//---------------------------------
// 
//---------------------------------

//---------------------------------
// 
//---------------------------------

//---------------------------------
// 
//---------------------------------