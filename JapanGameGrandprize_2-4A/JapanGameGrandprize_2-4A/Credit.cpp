#include "Credit.h"
#include"DxLib.h"

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
	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void Credit::Draw()const
{

	/*
	* DrawStirng(100,100,"�g�p����SE�ABGM",cr);
	DrawString(100,150,"�������ʉ��ŗV�ڂ��I",cr);
	DrawString(100,200,"DOVA-SYNDROME",cr);
	DrawString(100,250,"�t���[���ʉ��f�� ���炰�H��",cr);
	DrawString(100,300,"TAM Music Factory",cr);

	*/
}