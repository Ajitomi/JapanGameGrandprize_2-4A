#pragma once

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

	static Camera camera;

	/*static float camera_x;
	static float camera_y;*/

	//���͊Ԋu����		�f�o�b�N
	int input_margin;

	//�X�N���[�����x	�f�o�b�N
	float scroll_speed;	

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }
};