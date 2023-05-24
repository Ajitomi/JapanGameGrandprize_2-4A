#include "HarpyBullet.h"
#include "CameraWork.h"

//�n�[�s�B�̉������U���̈ړ����x
#define HARPY_BULLET_SPEED 8

//�n�[�s�B�̉������_���[�W
#define HARPY_BULLET_DAMAGE 5

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
HarpyBullet::HarpyBullet(const Location spawn_location, const Location player_location)
{
	
	Tick = 0;
	frame = 0;
	angle = 0;
	PHASE = 0;
	type = ENEMY_TYPE::WIND;
	location = spawn_location;
	radius = 5;
	speed = HARPY_BULLET_SPEED;
	image = 0;
	damage = HARPY_BULLET_DAMAGE;
	display_permit = FALSE;
	float radian; //�p�x
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
HarpyBullet::~HarpyBullet()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void HarpyBullet::Update()
{

	location.x += x_speed;
	location.y += y_speed;

	//switch (PHASE) {
	//case 0:
	//	if (Tick == 1) {
	//		frame = 0;
	//		display_permit = TRUE;
	//	}
	//	if (Tick % 2 == 0) {
	//				//HIT
	//			frame++;
	//			if (frame > 19) {
	//				display_permit = FALSE;
	//				PHASE++;
	//				Tick = 0;
	//		}
	//		else {
	//			frame++;
	//			if (frame > 14) {
	//				frame = 5;
	//			}
	//		}
	//	}
	//	break;
	///*case 1:
	//	if (Tick == 1) {
	//		TS[1].Extend_rate = 1;
	//		TS[1].frame = 0;
	//		TS[1].display_permit = TRUE;
	//		TS[1].BrendMode_ALPFA = 255;
	//	}
	//	if (Tick % 2 == 0) {
	//		TS[1].frame++;
	//		if (TS[1].frame > 19) {
	//			Tick = 0;
	//			ShotFlag[i] = 0;
	//		}
	//	}
	//	break;*/
	//default:
	//	break;
	//}

	/*if (TS[0].display_permit == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, TS[0].BrendMode_ALPFA);
		DrawRotaGraph(TS[0].Pos_x, TS[0].Pos_y, TS[0].Extend_rate, 0, TS[0].image_Array[TS[0].frame], TRUE, FALSE, FALSE);
	}

	if (TS[1].display_permit == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, TS[1].BrendMode_ALPFA);
		DrawRotaGraph(TS[1].Pos_x, TS[1].Pos_y, TS[1].Extend_rate, 0, TS[1].image_Array[TS[1].frame], TRUE, FALSE, FALSE);
	}*/
}

//-----------------------------------
//�`��̂�
//-----------------------------------
void HarpyBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}
