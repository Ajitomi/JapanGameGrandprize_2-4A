#pragma once
#include "Player.h"

class CameraWork
{
private:

protected:

	//�J�������W
	//static POINT camera;

	struct Camera
	{
		float x;
		float y;
	};

	//�I�u�W�F�N�g
	static Camera camera;
	Player* player;

	//���͊Ԋu����		�f�o�b�N
	int input_margin;

	//�X�N���[�����x	�f�o�b�N
	float scroll_speed;

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }
};