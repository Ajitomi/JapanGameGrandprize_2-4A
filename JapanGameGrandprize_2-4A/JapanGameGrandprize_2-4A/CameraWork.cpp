#include "CameraWork.h"
#include "PadInput.h"

CameraWork::Camera CameraWork::camera;

//#define DEBUG

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
CameraWork::CameraWork()
{
	camera.x = 0.0f;
	camera.y = 0.0f;

	input_margin = 0;
	
	speed = 0;

	count = 0;

	old_player = { 0,0 };

	player = nullptr;
	this->stage = nullptr;

	//�J�����̏�Ԃ��Œ�ɕύX
	state = STATE::FIXED;

	moveing_line = 400.0f;

	player_dir = true;
}

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
CameraWork::CameraWork(float camera_x, float camera_y, Player* player, Stage* stage)
{
	this->camera.x = camera_x;
	this->camera.y = camera_y;

	input_margin = 0;
	
	speed = 1.0f;

	count = 0;

	old_player = { 0,0 };

	this->player = player;
	this->stage = stage;

	//�J�����̏�Ԃ��Œ�ɕύX
	state = STATE::FIXED;

	moveing_line = 400.0f;

	player_dir = true;


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
	//clsDx();
	Camera player_p;
	player_p = { player->GetLocation().x, player->GetLocation().y };
	//float player_x = player->GetLocation().x;

	if (player_p.x > moveing_line) { state = STATE::MOVE; }

	if (state == STATE::MOVE) {

		

		//�}�b�v�̉E�[�ɒ�������~�߂�
		if (static_cast<float>(stage->GetMapSize().x * CHIP_SIZE - (SCREEN_WIDTH - moveing_line)) < ceilf(player->GetLocation().x)) {return;}

		//float player_speed = player_p.x - old_player.x;
		float player_speed = 1.0f;
		//printfDx("player_speed:%f\n", player_speed);

		if ((old_player.x != player_p.x) || (old_player.y != player_p.y)) {
			// �J�����̍��W���X�V
			camera.x = (player->GetLocation().x - moveing_line + player_speed) * speed;
			camera.y = player->GetLocation().y - 700;



			// �J�����͈̔͂��}�b�v�O�ɏo�Ȃ��悤�ɒ���
			if (camera.x < 0) {
				camera.x = 0;
			}
			/*else if (camera.x > stage->GetMapSize().x * CHIP_SIZE - moveing_line) {
				camera.x = stage->GetMapSize().x * CHIP_SIZE - moveing_line;
			}*/
			if (camera.y < 0) {
				camera.y = 0;
			}
			else if (camera.y > stage->GetMapSize().y * CHIP_SIZE - 700) {
				camera.y = stage->GetMapSize().y * CHIP_SIZE - 700;
			}


			////���E�E�[�Ŏ~�߂�
			//if ((stage->GetMapSize().x > player->GetLocation().x) && (stage->GetMapSize().x < player->GetLocation().x)) { return; }

			//float player_x = player->GetLocation().x;

			//if (count < 60) { count++; }
			//else { old_player.x = player->GetLocation().x; count = 0; }

			//printfDx("x:%f\ty:%f\n", player->GetLocation().x, player->GetLocation().y);

			//if (player->GetLocation().x < 500 && speed < 1.0) {
			//	speed = fmod(player_x, 50) * 0.1;
			//}
			//else if ((player->GetLocation().x > 620 && player->GetLocation().x < 1200) && old_player.x != player_x) {
			//	camera.x += speed * 0.01;
			//}

			////�v���C���[�̋����W����
		}
		old_player.x = player_p.x;
		old_player.y = player_p.y;


		{	//�v���C���[�̌���

			if (player_speed < 0) {
				player_dir = false;
			}
			else if (player_speed > 0) {
				player_dir = true;
			}

		}
	}

#ifdef DEBUG

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