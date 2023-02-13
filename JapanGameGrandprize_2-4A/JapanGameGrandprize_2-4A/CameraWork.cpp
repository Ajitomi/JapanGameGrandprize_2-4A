#include "CameraWork.h"
#include "PadInput.h"

CameraWork::Camera CameraWork::camera;

#define DEBUG

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
CameraWork::CameraWork()
{
	camera.x = 0.0f;
	camera.y = 0.0f;

	input_margin = 0;
	scroll_speed = 1;

	player = nullptr;
}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
CameraWork::CameraWork(float camera_x, float camera_y, Player* player)
{
	this->camera.x = camera_x;
	this->camera.y = camera_y;

	input_margin = 0;
	scroll_speed = 0.5f;

	this->player = player;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
CameraWork::~CameraWork()
{
	delete player;
}

//-----------------------------------
// �X�V
//-----------------------------------
void CameraWork::Update()
{
#ifdef DEBUG

	printfDx("x:%f\ty:%f\n", player->GetLocation().x, player->GetLocation().y);

	if (player->GetLocation().x < 600) {
		camera.x = 600 - player->GetLocationX();
	}


	if (input_margin < 10)
	{
		input_margin++;
	}
	else
	{

		//�X�N���[���X�s�[�h�_�E��
		if (CheckHitKey(KEY_INPUT_M))
		{
			if (scroll_speed > 0) { scroll_speed -= 1.0f; }
		}

		//�X�N���[���X�s�[�h�A�b�v
		else if (CheckHitKey(KEY_INPUT_L))
		{
			scroll_speed += 1.0f;
		}
	}

	//�X�N���[���ړ�
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		camera.y -= scroll_speed;
	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		camera.y += scroll_speed;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		camera.x += scroll_speed;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		camera.x -= scroll_speed;
	}
	input_margin = 0;

#endif // DEBUG

}