#pragma once
#include "Player.h"
#include "Stage/Stage.h"

class CameraWork
{
private:



protected:

	//�J�������W
	//static POINT camera;

	//�J�������W�\����
	struct Camera
	{
		float x;
		float y;
	};

	//�v���C���[�̋����W
	Camera old_player;

	//�J�����X�s�[�h
	float speed;

	//�J�E���g
	float count;

	//�I�u�W�F�N�g
	static Camera camera;
	Player* player;
	Stage* stage;

	//���͊Ԋu����		�f�o�b�N
	int input_margin;

	//�X�N���[�����x	�f�o�b�N
	float scroll_speed;

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player, Stage* stage);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }
};