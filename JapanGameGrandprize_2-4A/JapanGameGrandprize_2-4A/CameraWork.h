#pragma once
#include "Player.h"
#include "Stage/Stage.h"

class CameraWork
{

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
	//�v���C���[�̌���
	//FALSE: ��		TRUE:�E
	bool player_dir;

	//�J�����X�s�[�h
	float speed;

	//�J�E���g
	float count;


	//�ړ��J�nX���W
	float moveing_line;

	//�I�u�W�F�N�g
	static Camera camera;
	Player* player;
	Stage* stage;

	//���͊Ԋu����		�f�o�b�N
	int input_margin;

public:
	enum class STATE {
		MOVE,	//�ړ�
		FIXED	//�Œ�
	};


	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player, Stage* stage);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }



private:

	//�J�����̏��
	STATE state;
};
