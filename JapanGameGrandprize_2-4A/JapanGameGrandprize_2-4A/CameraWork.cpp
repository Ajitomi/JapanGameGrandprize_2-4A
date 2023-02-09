#include "CameraWork.h"
#include "PadInput.h"

CameraWork::CameraWork()
{
	camera_x = 0;
	camera_y = 0;

	input_margin = 0;
	scroll_speed = 1;	
}

CameraWork::CameraWork(float camera_x, float camera_y)
{
	this->camera_x = camera_x;
	this->camera_y = camera_y;

	input_margin = 0;
	scroll_speed = 1;
}

CameraWork::~CameraWork()
{
}

void CameraWork::Update()
{

	if (input_margin < 10) {
		input_margin++;
	}
	else
	{

		//�X�N���[���X�s�[�h�_�E��
		if (CheckHitKey(KEY_INPUT_M))
		{
			if (scroll_speed > 0) { scroll_speed--; }
		}

		//�X�N���[���X�s�[�h�A�b�v
		else if (CheckHitKey(KEY_INPUT_L))
		{
			scroll_speed++;
		}

		//�X�N���[���ړ�
		if (CheckHitKey(KEY_INPUT_UP))
		{
			camera_y--;
		}
		else if (CheckHitKey(KEY_INPUT_DOWN)) 
		{
			camera_y++;
		}
		else if (CheckHitKey(KEY_INPUT_LEFT)) 
		{
			camera_x--;
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT)) 
		{
			camera_x--;
		}
		input_margin = 0;
	}
}
