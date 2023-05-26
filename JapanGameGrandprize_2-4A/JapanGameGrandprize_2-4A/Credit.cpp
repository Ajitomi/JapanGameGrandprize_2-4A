#include "Credit.h"
#include"DxLib.h"

//�\�����鎞��
#define DISPLAY 240

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
	if (++time % DISPLAY == 0)
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
	SetFontSize(64);                             //�T�C�Y��64�ɕύX
	SetFontThickness(8);                         //������8�ɕύX
	ChangeFont("�l�r ����");                     //��ނ�MS�����ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);     //�A���`�G�C���A�X�t�H���g�ɕύX

	DrawString(400,100,"�g�p����SE  BGM\n",cr);

	SetFontSize(34);                             //�T�C�Y��35�ɕύX

	DrawString(400,200,"�t���[���y�f�� H/MIX GALLERY\n",cr);
	DrawString(400,250,"�t���[���ʉ��f�� ���炰�H��\n",cr); 
	DrawString(400,300,"�������ʉ��ŗV�ڂ��I\n",cr); 
	DrawString(400,350,"TAM Music Factory\n",cr);
	DrawString(400,400,"DOVA-SYNDROME\n",cr);
	DrawString(400,450,"���ʉ����{\n", cr); 
	DrawString(400,500, "BOOTH\n", cr);

	
}