#include "LineCollider.h"
#include "CameraWork.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
LineCollider_t::LineCollider_t()
{
	//��΍��W
	vector[LINE_START] = { 0,0 };
	vector[LINE_END] = { SCREEN_WIDTH, SCREEN_HEIGHT };
	
	location = GetMiddlePoint(vector[LINE_START], vector[LINE_END]);
	Relativize();
}

//------------------------------------
// �R���X�g���N�^
//------------------------------------
LineCollider_t::LineCollider_t(Location point1, Location point2)
{
	//��΍��W
	vector[LINE_START] = point1;
	vector[1] = point2;

	location = GetMiddlePoint(vector[LINE_START], vector[LINE_END]);
	Relativize();
}

//--------------------------------------
// �f�X�g���N�^
//--------------------------------------
LineCollider_t::~LineCollider_t()
{

}

//--------------------------------------
// �`��
//--------------------------------------
void LineCollider_t::Draw()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawLineAA(
		GetLocation(LINE_START).x - CameraWork::GetCamera().x, 
		GetLocation(LINE_START).y - CameraWork::GetCamera().y,
		GetLocation(LINE_END).x - CameraWork::GetCamera().x,
		GetLocation(LINE_END).y - CameraWork::GetCamera().y,
		0xE9FF00, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawCircle
}

//-----------------------------------
// �_�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider_t::HitDot(Location point)const
{
	bool is_hit = false;
	float closs_product;

	Location vector1 =
		GetLocation(LINE_END) - GetLocation(LINE_START);
	Location vector2 =
		point - GetLocation(LINE_START);

	closs_product = (vector1.x * vector2.y) - (vector1.y * vector2.x);

	if (closs_product == 0)
	{
		is_hit = true;
	}

	return is_hit;
}

//-----------------------------------
// SphereCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider_t::HitSphere(const SphereCollider* sphere)const
{
	bool is_hit = false;
	return is_hit;
}

//-----------------------------------
// BoxCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider_t::HitBox(const BoxCollider* box)const
{
	bool is_hit = false;
	return is_hit;
}

//-----------------------------------
// LineCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider_t::HitLine(const LineCollider_t* line)const
{
	bool is_hit = false;
	return is_hit;
}

//-----------------------------------------------------
// ���̒[�̍��W�̎擾 �n�_���I�_�Ԃ� �f�t�H���g�͎n�_
//-----------------------------------------------------
Location LineCollider_t::GetLocation(int index)const
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
void LineCollider_t::SetLocation(Location location, int index)
{
	if (index < 2)
	{
		vector[LINE_START] = MakeTip(LINE_START);
		vector[LINE_END] = MakeTip(LINE_END);
		vector[index] = location;
		this->location = GetMiddlePoint(vector[LINE_START], vector[LINE_END]);
		Relativize();
	}
}

//-----------------------------------
// SphereCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitSphere(class SphereCollider* sphere_collider)
{

	bool ret = false; //�Ԃ�l

	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float unit_vector;	//�P�ʃx�N�g��
	float shortest_distance; //�����Ɖ~�̍ŒZ�̋���

	float inner_product[2]; //����
	float center_distance[2]; //�~�̒��S�Ƃ̋���(0:�����̎n�_�@1:�����̏I�_)

	//������LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
	vector_x[0] = location[1].x - location[0].x;
	vector_y[0] = location[1].y - location[0].y;

	//������LineCollider�̎n�_��phereCollider�̒��S�Ƃ̃x�N�g���̌v�Z
	vector_x[1] = sphere_collider->GetLocation().x - location[0].x;
	vector_y[1] = sphere_collider->GetLocation().y - location[0].y;

	//������LineCollider�̏I�_��SphereCollider�̒��S�Ƃ̃x�N�g���̌v�Z
	vector_x[2] = sphere_collider->GetLocation().x - location[1].x;
	vector_y[2] = sphere_collider->GetLocation().y - location[1].y;

	//�P�ʃx�N�g���̌v�Z
	unit_vector = sqrtf(powf(vector_x[0], 2) + powf(vector_y[0], 2));

	//�ŒZ�����̌v�Z
	shortest_distance = (vector_x[1] * (vector_x[0] / unit_vector)) 
						- (vector_y[1] * (vector_y[0] / unit_vector));

	if (fabsf(shortest_distance) <= sphere_collider->GetRadius())
	{
		//���ς̌v�Z
		for (int i = 0; i < 2; i++)
		{
			inner_product[i] = (vector_x[i + 1] * vector_x[0]) 
								- (vector_y[i + 1] * vector_y[0]);
		}
		//�~�̒��S�Ƃ̋����̌v�Z
		for (int i = 0; i < 2; i++)
		{
			center_distance[i] = sqrtf(powf(vector_x[i + 1], 2) + powf(vector_y[i + 1], 2));
		}

		if ((inner_product[0] * inner_product[1] <= 0.0f) 
				|| (center_distance[0] < sphere_collider->GetRadius()) 
					||(center_distance[1] < sphere_collider->GetRadius()))
		{
			ret = true;
		}
	}

	return ret;
}

//-----------------------------------
// BoxCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitBox(class BoxCollider* box_collider)
{
	bool ret = false; //�Ԃ�l

	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float outer_product[4]; //�O��

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];
	
	bool sign = false; //�ŏ��̊O�ς̕���(true:���̐��Afalse:���̐�)

	//�����̓����蔻��͈̔͂̌v�Z
	if (location[0].x <= location[1].x)
	{
		my_x[0] = location[0].x;
		my_x[1] = location[1].x;

	}
	else
	{
		my_x[0] = location[1].x;
		my_x[1] = location[0].x;
	}

	if (location[0].y <= location[1].y)
	{
		my_y[0] = location[0].y;
		my_y[1] = location[1].y;
	}
	else
	{
		my_y[0] = location[1].y;
		my_y[1] = location[0].y;
	}

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;


	if ((my_x[0] < sub_x[1]) && (my_x[1] < sub_x[1]) 
			&& (my_y[0] < sub_y[1]) && (sub_y[0] < my_y[1]))
	{
		//������LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
		vector_x[0] = location[1].x - location[0].x;
		vector_y[0] = location[1].y - location[0].y;

		//������LineCollider�̎n�_�ƍ���̊p�Ƃ̃x�N�g��
		vector_x[1] = box_collider->GetLocation().x - location[0].x;
		vector_y[1] = box_collider->GetLocation().y - location[0].y;

		//������LineCollider�̎n�_�ƉE���̊p�Ƃ̃x�N�g��
		vector_x[2] = (box_collider->GetLocation().x 
						+ box_collider->GetArea().width) - location[0].x;
		vector_y[2] = (box_collider->GetLocation().y 
						+ box_collider->GetArea().height) - location[0].y;

		//�e���_�ƊO�ς̌v�Z
		for (int i = 0, n = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				outer_product[n++] = (vector_x[0] * vector_y[i]) 
					                    - (vector_y[0] * vector_x[j]);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (outer_product[i] == 0) //�O�ς̒l��0�Ȃ瓖�����Ă���
			{
				ret = true;
				break;
			}

			if (i == 0)
			{
				//�E��̊p�Ƃ̊O�ς̕����̎擾
				sign = signbit(outer_product[0]);
			}
			else
			{
			
				if (sign != signbit(outer_product[i]))	//����̊p�Ƃ̊O�ς̕�����������瓖�����Ă���
				{
					ret = true;
					break;
				}
			}
		}
	}
	
	return ret;
}

//-----------------------------------
// LineCollider�Ƃ̓����蔻��
//-----------------------------------
bool LineCollider::HitLine(LineCollider* line_collider)
{

	bool ret = false; //�Ԃ�l

	/*������LineCollider�̎n�_���N�_�ɂ��ďo���x�N�g��*/
	float vector_x[3]; //X���W�̃x�N�g��
	float vector_y[3]; //Y���W�̃x�N�g��

	float outer_product[2]; //�O��

	//������LineCollider�̎n�_�ƏI�_�Ƃ̃x�N�g���̌v�Z
	vector_x[0] = location[1].x - location[0].x;
	vector_y[0] = location[1].y - location[0].y;

	//������LineCollider�̎n�_�Ƒ����LineCollider�̎n�_�Ƃ̃x�N�g���̌v�Z
	vector_x[1] = line_collider->GetLocation(0).x - location[0].x;
	vector_y[1] = line_collider->GetLocation(0).y - location[0].y;

	//������LineCollider�̎n�_�Ƒ����LineCollider�̏I�_�Ƃ̃x�N�g���̌v�Z
	vector_x[2] = line_collider->GetLocation(1).x - location[0].x;
	vector_y[2] = line_collider->GetLocation(1).y - location[0].y;

	//�O�ς̌v�Z
	for (int i = 0; i < 2; i++)
	{
		outer_product[i] = (vector_x[0] * vector_y[i + 1]) 
			                - (vector_x[i + 1] * vector_y[0]);
	}

	//�����蔻��̔��f
	if (outer_product[0] * outer_product[1] <= 0.0f)
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// ���̒[�̍��W�̎擾
//-----------------------------------
Location  LineCollider::GetLocation(int i)const
{
	return location[i];
}

//-----------------------------------
// ���S���W�̐ݒ�
//-----------------------------------
void  LineCollider::SetLocation(Location location, int i)
{
	this->location[i] = location;
}