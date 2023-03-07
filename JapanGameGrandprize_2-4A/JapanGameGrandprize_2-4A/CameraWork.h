#pragma once
#include "Define.h"
#include "Player.h"
#include "Stage/Stage.h"

class CameraWork
{
public:
	//�J�������W�\����
	struct Camera
	{
		float x;
		float y;
	};

protected:

	//�J�������W
	//static POINT camera;

	//�v���C���[�̋����W
	Camera old_player;
	//�v���C���[�̌���
	//FALSE: ��		TRUE:�E
	bool player_dir;
	bool player_dir_y;

	//�J�����X�s�[�h
	float speed;

	//�J�E���g
	float count;

	//�ړ��J�nX���W
	float moveing_line;

	//�I�u�W�F�N�g
	static Location camera;
	Player* player;
	Stage* stage;

	//���͊Ԋu����		�f�o�b�N
	int input_margin;
public:

	enum class STATE 
	{
		MOVE,	//�ړ�
		FIXED	//�Œ�
	};

	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player, Stage* stage);

	~CameraWork();
	void Update();
	static Location GetCamera() { return camera; }
private:

	//�J�����̏��
	STATE state;
};