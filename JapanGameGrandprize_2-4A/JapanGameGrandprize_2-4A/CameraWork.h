#pragma once
class CameraWork
{
private:

protected:

	//�J�������W
	float camera_x;
	float camera_y;

	//���͊Ԋu����		�f�o�b�N
	int input_margin;

	//�X�N���[�����x	�f�o�b�N
	int scroll_speed;	

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y);

	~CameraWork();
	void Update();
};

