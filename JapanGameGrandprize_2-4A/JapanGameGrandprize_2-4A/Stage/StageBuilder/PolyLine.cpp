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

	location = (bend_points[0] + bend_points[size - 1]) / 2;

	MakeLocation();

#ifdef _STAGE_BUILDER


#endif
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

	location = (bend_points[0]->GetLocation() +
		bend_points[bend_points.size() - 1]->GetLocation()) / 2;

	MakeLocation();

#ifdef _STAGE_BUILDER


#endif
}

//-------------------------------------
// �R�s�[�R���X�g���N�^ 
//-------------------------------------
PolyLine::PolyLine(const PolyLine &poly_line)
{
	for (auto it : poly_line.bend_points)
	{
		this->bend_points.push_back(new SphereCollider(*it));
	}

	for (auto it : poly_line.lines)
	{
		this->lines.push_back(new LineCollider(*it));
	}

#ifdef _STAGE_BUILDER

	pivot = poly_line.pivot;

#endif
}

//---------------------------------
// �f�X�g���N�^
//---------------------------------
PolyLine::~PolyLine()
{
	for (int i = 0; i < bend_points.size(); i++)
	{
		delete bend_points[i];
	}
	bend_points.clear();

	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	lines.clear();
}

//---------------------------------
// �X�V
//---------------------------------
void PolyLine::Update()
{
#ifdef _STAGE_BUILDER
	if (old_location != location)
	{
		Location distance = location - old_location;
		for (auto it : lines)
		{
			it->ColliderBase::SetLocation
			(it->ColliderBase::GetLocation() + distance);
		}
	}
#endif

	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->SetLocation(bend_points[i]->GetLocation(), LINE_START);
		lines[i]->SetLocation(bend_points[i + 1]->GetLocation(), LINE_END);
	}

	MakeLocation();



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

	for (auto it : bend_points)
	{
		it->Draw();
	}

#ifdef _STAGE_BUILDER

	pivot.Draw();

#endif
}

//---------------------------------
// SphereCollider�Ƃ̓����蔻��
//---------------------------------
bool PolyLine::HitSphere(const class SphereCollider* sphere_collider)const
{
	bool is_hit = false;
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->HitSphere(sphere_collider))
		{
			return true;
		}
	}

	return is_hit;
}

//---------------------------------
// BoxCollider�Ƃ̓����蔻��
//---------------------------------
bool PolyLine::HitBox(const class BoxCollider* box_collider)const
{
	bool is_hit = false;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->HitBox(box_collider))
		{
			return true;
		}
	}

	return is_hit;
}

//---------------------------------
// LineCollider�Ƃ̓����蔻��
//---------------------------------
bool PolyLine::HitLine(const class LineCollider* line_collider)const
{
	bool is_hit = false;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->HitLine(line_collider))
		{
			return true;
		}
	}

	return is_hit;
}

//-------------------------------
// �����蔻��`�F�b�N
//------------------------------
bool PolyLine::HitCheck(ColliderBase* collider)const
{
	bool is_hit = false;

	collider = dynamic_cast<BoxCollider*>(collider);
	if (collider)
	{
		return HitBox(dynamic_cast<BoxCollider*>(collider));
	}

	collider = dynamic_cast<SphereCollider*>(collider);
	if (collider)
	{
		return HitSphere(dynamic_cast<SphereCollider*>(collider));
	}

	collider = dynamic_cast<LineCollider*>(collider);
	if (collider)
	{
		return HitLine(dynamic_cast<LineCollider*>(collider));
	}

	return is_hit;
}

//---------------------------------
// �_�̍폜
//---------------------------------
void PolyLine::DeleteBendPoint(int index)
{
	delete bend_points[index];
	bend_points.erase(bend_points.begin() + index);

	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	lines.clear();

	if (2 <= bend_points.size())
	{
		for (int i = 0; i < bend_points.size() - 1; i++)
		{
			lines.push_back(new LineCollider(bend_points[i]->GetLocation(), 
				bend_points[i + 1]->GetLocation()));
		}
	}
}

//---------------------------------------
// ���S���W�̌v�Z�A�Čv�Z
//---------------------------------------
void PolyLine::MakeLocation()
{
	Location points[2] =
	{
		bend_points[0]->GetLocation(),
		bend_points[bend_points.size() - 1]->GetLocation()
	};
	Location middle = (points[0] + points[1]) / 2;

	SetLocation(middle);
#ifdef _STAGE_BUILDER
	pivot.SetLocation(middle);
	old_location = middle;
#endif
}