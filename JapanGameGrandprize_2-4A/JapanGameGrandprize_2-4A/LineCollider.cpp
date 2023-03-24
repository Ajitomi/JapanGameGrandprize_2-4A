#include "LineCollider.h"
#include "CameraWork.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
LineCollider::LineCollider()
{
	//��΍��W
	vector[LINE_START] = { 0,0 };
	vector[LINE_END] = { SCREEN_WIDTH, SCREEN_HEIGHT };
	
	location = GetMiddlePoint();
	Relativize();
}

//------------------------------------
// �R���X�g���N�^
//------------------------------------
LineCollider::LineCollider(Location point1, Location point2)
{
	//�_����Ȃ����Ƃ�ۏ؂���
	if (point1 == point2)
	{
		point2.x += 1;
		point2.y += 1;
	}
	//��΍��W
	vector[LINE_START] = point1;
	vector[LINE_END] = point2;

	location = GetMiddlePoint();
	Relativize();
}

//--------------------------------------
// �f�X�g���N�^
//--------------------------------------
LineCollider::~LineCollider()
{

}

//--------------------------------------
// �`��
//--------------------------------------
void LineCollider::Draw()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawLineAA(
		GetLocation(LINE_START).x - CameraWork::GetCamera().x, 
		GetLocation(LINE_START).y - CameraWork::GetCamera().y,
		GetLocation(LINE_END).x - CameraWork::GetCamera().x,
		GetLocation(LINE_END).y - CameraWork::GetCamera().y,
		0xE9FF00, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//-----------------------------------
// �_�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitDot(Location point)const
{
	bool is_hit = false;
	float cross_product;

	Location vector1 =
		GetLocation(LINE_START) - GetLocation(LINE_END);
	Location vector2 =
		point - GetLocation(LINE_END);

	cross_product = (vector1.x * vector2.y) - (vector1.y * vector2.x);
	//�����͈͓̔����ǂ���
	if ((GetMin() <= point) && point <= GetMax())
	{
		if (cross_product == 0)
		{
			is_hit = true;
		}
	}


	return is_hit;
}

//-----------------------------------
// SphereCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitSphere(const SphereCollider* sphere)const
{
	bool is_hit = false;
	Location vector1 =
		GetLocation(LINE_END) - GetLocation(LINE_START);
	Location vector2 =
		sphere->GetLocation() - GetLocation(LINE_START);

	float len = powf(vector1.x * vector1.x + vector1.y * vector1.y, 0.5);

	Location unit_vector;
	unit_vector.x = vector1.x / len;
	unit_vector.y = vector1.y / len;

	float distance_near_pos = unit_vector.x * vector2.x
		+ unit_vector.y * vector2.y;

	Location near_pos;

	near_pos.x = unit_vector.x * distance_near_pos;
	near_pos.y = unit_vector.y * distance_near_pos;

	float distance_sphere_near_pos;

	distance_sphere_near_pos =
		powf(powf(near_pos.x - vector2.x, 2.0) + powf(near_pos.y - vector2.y, 2.0), 0.5);

	if (distance_sphere_near_pos > sphere->GetRadius())
	{
		return false;
	}

	bool is_start_acute = CheckIsAcute(GetLocation(LINE_END)
		- GetLocation(LINE_START), vector2);
	bool is_end_acute 
		= CheckIsAcute(GetLocation(LINE_END) - GetLocation(LINE_START)
			,sphere->GetLocation() - GetLocation(LINE_END) );

	if (is_start_acute ^ is_end_acute)
	{
		is_hit = true;
	}

	float distance_tips_sphere
		= MakeScalar(sphere->GetLocation() - GetLocation(LINE_START));
	if (distance_tips_sphere <= sphere->GetRadius())
	{
		is_hit = true;
	}
	distance_tips_sphere
		= MakeScalar(sphere->GetLocation() - GetLocation(LINE_END));
	if (distance_tips_sphere <= sphere->GetRadius())
	{
		is_hit = true;
	}

	return is_hit;
}

//-----------------------------------
// BoxCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitBox(const BoxCollider* box)const
{
	bool is_hit = false;
	bool box_ishit = false;
	float sign = 0;

	Location vertex[4] =
	{
		//�l��
		{box->GetLocation().x - box->GetArea().width / 2,
		box->GetLocation().y - box->GetArea().height / 2 },

		{box->GetLocation().x + box->GetArea().width / 2,
		box->GetLocation().y - box->GetArea().height / 2 },

		{box->GetLocation().x - box->GetArea().width / 2,
		box->GetLocation().y + box->GetArea().height / 2 },

		{box->GetLocation().x + box->GetArea().width / 2,
		box->GetLocation().y + box->GetArea().height / 2},

	};

	for (int i = 0; i < 4; i++)
	{
		if ((GetMin() <= vertex[i]) && vertex[i] <= GetMax())
		{
			box_ishit = true;
		}
	}
	if (box_ishit == false)return false; //�������͂��l�p�`�ɂ��瓖�����ĂȂ�

	
	for (int i = 0; i < 4; i++)
	{
		float closs_product = 0;

		Location vector1 =
			GetLocation(LINE_START) - GetLocation(LINE_END);
		Location vector2 =
			vertex[i] - GetLocation(LINE_END);

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
// LineCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitLine(const LineCollider* line)const
{
	bool is_hit = false;

	Location this_vector
		= this->GetLocation(LINE_END) - this->GetLocation(LINE_START);
	 
	Location arg_vector
		= line->GetLocation(LINE_END) - line->GetLocation(LINE_START);

	float cross_product[2];
	cross_product[0]
		= MakeCrossProduct(this_vector,
			line->GetLocation(LINE_START) - this->GetLocation(LINE_START));
	
	cross_product[1]
		= MakeCrossProduct(this_vector,
			line->GetLocation(LINE_END) - this->GetLocation(LINE_START));

	if (0 < cross_product[0] * cross_product[1])
	{
		return false;
	}

	cross_product[0]
		= MakeCrossProduct(arg_vector,
			this->GetLocation(LINE_START) - line->GetLocation(LINE_START));
	
	cross_product[1]
		= MakeCrossProduct(arg_vector,
			this->GetLocation(LINE_END) - line->GetLocation(LINE_START));

	if (cross_product[0] * cross_product[1] <= 0)
	{
		is_hit = true;
	}


	return is_hit;
}

//-----------------------------------------------------
// ���̒[�̍��W�̎擾 �n�_���I�_�Ԃ� �f�t�H���g�͎n�_
//-----------------------------------------------------
Location LineCollider::GetLocation(int index)const
{
	if (index < 2)
	{
		return MakeTip(index);
	}
	else
	{
		return MakeTip(LINE_START);
	}
}

//--------------------------------------------------
// �n�_�A�I�_���W�̐ݒ� �����F���W�A�n�_�F0 �I�_�F1
//--------------------------------------------------
void LineCollider::SetLocation(Location location, int index)
{
	if (index < 2)
	{
		vector[LINE_START] = MakeTip(LINE_START);
		vector[LINE_END] = MakeTip(LINE_END);
		vector[index] = location;
		this->location = GetMiddlePoint();
		Relativize();
	}
}
