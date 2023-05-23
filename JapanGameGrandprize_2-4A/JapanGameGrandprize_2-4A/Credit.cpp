#include "Credit.h"
#include"DxLib.h"

//�\�����鎞��
#define DISPLAY 60

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Credit::Credit()
{
	display_time = 0;
	time = 0;
	cr = GetColor(255, 255, 255); 
}


//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Credit::~Credit()
{

}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* Credit::Update()
{
	if (++time % 120 == 0)
	{
		if (++display_time > DISPLAY == 0)
		{
			return nullptr;
		}
	}
	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void Credit::Draw()const
{
	DrawString(100,100,"�g�p����SE�ABGM\n",cr);
	DrawString(100,150,"�������ʉ��ŗV�ڂ��I\n",cr);
	DrawString(100,200,"DOVA-SYNDROME\n",cr);
	DrawString(100,250,"�t���[���ʉ��f�� ���炰�H��\n",cr);
	DrawString(100,300,"TAM Music Factory\n",cr);
	DrawString(100,350,"���ʉ����{\n",cr);
	
}