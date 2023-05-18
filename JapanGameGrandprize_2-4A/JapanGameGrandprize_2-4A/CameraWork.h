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

	enum class STATE
	{
		MOVE,	//�ړ�
		BOSS,	//�{�X����
		FIXED	//�Œ�
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

private:

	//�J�����̏��
	static STATE state;
	bool is_lock;

public:

	

	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player, Stage* stage, short stage_num);

	~CameraWork();
	void Update();
	static Location GetCamera() { return camera; }
	static STATE GetCameraState() { return state; }
	bool GetCameraLock(){ return is_lock; }
	void SetCameraLock(bool is_lock) { this->is_lock = is_lock; }
	void SetCameraState(STATE state) { this->state = state; }
};