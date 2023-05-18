#include "LastBossSpecialMoves.h"
#include "DxLib.h"
#include "CameraWork.h"
#define _USE_MATH_DEFINES
#include <math.h>

//�G�t�F�N�g�̐�
#define EFFECT_NUM 7

//�`���[�W�G�t�F�N�g�̐�
#define CHARGE_EFFECT_NUM 10 

//�{�̂̉摜�̖���
#define EFFECT_BODY_IMAGES 15

//�I���n�_
#define END_POINT SCREEN_HEIGHT / 2

//�G�t�F�N�g�̖{�̂̃A�j���[�V����
#define EFFECT_BODY_ANIMATION 2

//�����x�̌��Z��
#define SUB_ALPFA_BREND 25

//�����x�̍ő�l
#define MAX_ALPFA_BREND 255

//�����X�s�[�h
#define EFFECT_SPEED 3

//�`���[�W�G�t�F�N�g�̋���
#define CHARGE_EFFECT_DISTANCE 200

//�_���[�W
#define SPECIAL_MOVES_DAMAGE 500

//�`���[�W����
#define CHARGE_TIME 60 * 5

#define SPAWN_INTERVAL 5

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
LastBossSpecialMoves::LastBossSpecialMoves(const Location spawn_location)
{
	end = false;
	effect = new Effect[EFFECT_NUM];

	//�G�t�F�N�g�̏�����
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		effect[i].draw = false;
		effect[i].location = spawn_location;
		effect[i].location.y = -50;
		effect[i].animation = 0;
		if ((1 <= i) && (i < 4))
		{
			effect[i].size = 0.05;
		}
		else
		{
			effect[i].size = 0.3;
		}
		effect[i].angle = 0.0;
		effect[i].alpfa_brend = MAX_ALPFA_BREND;
	}

	effect[6].size = 0.05;

	/*�摜�̓ǂݍ���*/
	effect[0].images = new int[EFFECT_BODY_IMAGES];
	for (int i = 1; i < EFFECT_NUM; i++)
	{
		effect[i].images = new int[1];
	}

	//�{�̂̉摜
	LoadDivGraph("Images/Enemy/SpecialMoves/��_��.png", EFFECT_BODY_IMAGES, 5, 3, 480, 480, effect[0].images);

	//�Ռ��g�̉摜
	for (int i = 1; i < 4; i++)
	{
		effect[i].images[0] = LoadGraph("Images/Enemy/SpecialMoves/Wave.png");
	}

	//�I�[���̉摜
	for (int i = 4; i < 6; i++)
	{
		effect[i].images[0] = LoadGraph("Images/Enemy/SpecialMoves/nc183332.png");
	}

	//����G�t�F�N�g�̉摜
	effect[6].images[0] = LoadGraph("Images/Enemy/SpecialMoves/�y��G�t�F�N�g-2.png");

	charge_effect = new Effect[CHARGE_EFFECT_NUM];
	for (int i = 0; i < CHARGE_EFFECT_NUM; i++)
	{
		charge_effect[i].draw = false;
		charge_effect[i].location.x = effect[0].location.x 
			+ GetRand(CHARGE_EFFECT_DISTANCE * 2) - CHARGE_EFFECT_DISTANCE;
		charge_effect[i].location.y = effect[0].location.y + GetRand(CHARGE_EFFECT_DISTANCE);
		charge_effect[i].images = new int[EFFECT_BODY_IMAGES];
		LoadDivGraph("Images/Enemy/SpecialMoves/��_��.png", EFFECT_BODY_IMAGES, 5, 3, 480, 480, charge_effect[i].images);
		charge_effect[i].animation = GetRand(EFFECT_BODY_IMAGES - 1);
		charge_effect[i].size = (static_cast<double>(GetRand(10)) + 10)/ 100.0;
		charge_effect[i].angle = 0.0;
		charge_effect[i].alpfa_brend = GetRand(55) + 200;
	}

	tick = 0;

	state = SPECIAL_MOVES_STATE::CHARGE;

}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
LastBossSpecialMoves::~LastBossSpecialMoves()
{
	//�摜�̍폜
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < EFFECT_BODY_IMAGES; j++)
			{
				DeleteGraph(effect[i].images[j]);
			}
		}
		else
		{
			DeleteGraph(effect[i].images[0]);
		}
		delete[] effect[i].images;
	}

	//�G�t�F�N�g�̍폜
	delete[] effect;

	for (int i = 0; i < CHARGE_EFFECT_NUM; i++)
	{
		for (int j = 0; j < EFFECT_BODY_IMAGES; j++)
		{
			charge_effect[i].images[j];
		}
		delete[] charge_effect[i].images;
	}
	delete[] charge_effect;
}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBossSpecialMoves::Update()
{
	tick++;

	switch (state)
	{
	case SPECIAL_MOVES_STATE::CHARGE:
	{
		int speed[2] = { EFFECT_SPEED ,EFFECT_SPEED };

		float radian = 0;

		for (int i = 0; i < CHARGE_EFFECT_NUM; i++)
		{
			if (charge_effect[i].draw)
			{
				radian = atan2f(effect[0].location.y - charge_effect[i].location.y,
					effect[0].location.x - charge_effect[i].location.x);

				speed[0] = static_cast<int>(EFFECT_SPEED * cosf(radian));
				speed[1] = static_cast<int>(EFFECT_SPEED * sinf(radian));

				charge_effect[i].location.x += speed[0];
				charge_effect[i].location.y += speed[1];


				if (charge_effect[i].location.y <= -50)
				{
					charge_effect[i].draw = false;
				}

				if (tick % EFFECT_BODY_ANIMATION == 0) //�A�j���[�V����
				{
					charge_effect[i].animation = (charge_effect[i].animation++) % EFFECT_BODY_IMAGES;
				}
			}
			else
			{
				if (tick % SPAWN_INTERVAL == 0)
				{
					charge_effect[i].draw = true;
					charge_effect[i].location.x = effect[0].location.x
						+ GetRand(CHARGE_EFFECT_DISTANCE * 2) - CHARGE_EFFECT_DISTANCE;
					charge_effect[i].location.y = effect[0].location.y +
						GetRand(CHARGE_EFFECT_DISTANCE);
					charge_effect[i].alpfa_brend = GetRand(55) + 200;
				}
			}
		}

		if (CHARGE_TIME < tick) //�`���[�W�I��
		{
			state = SPECIAL_MOVES_STATE::FALL;
		}
	}
		break;
	case SPECIAL_MOVES_STATE::FALL:
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			switch (i)
			{
			case 0: //�{��
				effect[i].location.y += EFFECT_SPEED;
				if (!effect[i].draw)
				{
					effect[i].draw = true;
				}
				if (tick % EFFECT_BODY_ANIMATION == 0) //�{�̂̃A�j���[�V����
				{
					if (effect[i].draw)
					{
						effect[i].animation = (effect[0].animation++) % EFFECT_BODY_IMAGES;
					}
				}
				break;
			case 4: //�I�[��
			case 5:
				effect[i].location.y += EFFECT_SPEED;

				if (effect[i].draw)
				{
					effect[i].alpfa_brend -= SUB_ALPFA_BREND;

					if (effect[i].alpfa_brend < 0)
					{
						effect[i].alpfa_brend = MAX_ALPFA_BREND;
						effect[i].draw = false;
					}
				}
				else
				{
					if (tick % ((rand() % 3 + 1) * 5) == 0)
					{
						effect[i].angle = (static_cast<double>(tick % 8) * 45) * (M_PI / 180);
						effect[i].draw = true;
					}
				}
				break;
			case 1:
			case 2:
			case 3:
			case 6:
				break;
				break;
			default:
				break;
			}
		}

		if (END_POINT < effect[0].location.y) //�I���n�_�ɓ��B
		{
			state = SPECIAL_MOVES_STATE::LANDING;
			for (int i = 0; i < EFFECT_NUM; i++)
			{
				switch (i)
				{
				case 1:
				case 2:
				case 3:
					effect[i].location = effect[0].location;
					effect[i].draw = true;
					break;
				case 4:
				case 5:
					effect[i].draw = false;
					break;
				case 6:
					effect[i].location = effect[0].location;
					break;
				case 0:
				default:
					break;
				}
			}
		}
		break;
	case SPECIAL_MOVES_STATE::LANDING:
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			switch (i)
			{
			case 0: //�{��
				effect[i].size -= 0.0181;

				if ((effect[i].draw) && (effect[i].size < 0.000))
				{
					effect[i].draw = false;
					effect[6].draw = true;
				}
				
				break;
			case 1:
			case 2:
			case 3:
				if (effect[i].size > 60)
				{
					effect[i].draw = false;
					end = true;
				}
				else
				{
					effect[i].size *= 1.1;
				}

				effect[i].location.x = effect[0].location.x +
					(static_cast<double>(rand() % 40) - 20) * (effect[i].size / 3);		//-20 �` 19
				effect[i].location.y = effect[0].location.y +
					(static_cast<double>(rand() % 40) - 20) * (effect[i].size / 3);		//-20 �` 19
				break;			
			case 6: //����
				if (effect[i].draw)
				{
					effect[i].size *= 1.20;

					if (effect[i].size > 1.5)
					{
						effect[i].draw = false;
					}
				}
				break;
			case 4: //�I�[��
			case 5:
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	
}

//-----------------------------------
//�`��
//-----------------------------------
void LastBossSpecialMoves::Draw() const
{
	Location draw_location = {};
	Location camera = CameraWork::GetCamera();
 	if (state == SPECIAL_MOVES_STATE::CHARGE)
	{
		for (int i = 0; i < CHARGE_EFFECT_NUM; i++)
		{
			if (charge_effect[i].draw)
			{
				draw_location = charge_effect[i].location - camera;	//�`����W�̌v�Z

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, charge_effect[i].alpfa_brend);

				DrawRotaGraphF(draw_location.x, draw_location.y, charge_effect[i].size,
					charge_effect[i].angle, charge_effect[i].images[charge_effect[i].animation], TRUE, FALSE, FALSE);
			}
		}
	}
	else
	{
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (effect[i].draw)
			{
				draw_location = effect[i].location - camera;	//�`����W�̌v�Z

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, effect[i].alpfa_brend);

				DrawRotaGraphF(draw_location.x, draw_location.y, effect[i].size,
					effect[i].angle, effect[i].images[effect[i].animation], TRUE, FALSE, FALSE);
			}
		}
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//�_���[�W�̎擾
int LastBossSpecialMoves::GetDamage() const
{
	return SPECIAL_MOVES_DAMAGE;
}

//�I�����̎擾
bool LastBossSpecialMoves::GetEnd() const
{
	return end;
}

//�`���[�W�I��
bool LastBossSpecialMoves::EndCharge() const
{
	bool ret = false;

	if (state != SPECIAL_MOVES_STATE::CHARGE)
	{
		ret = true;
	}

	return ret;
}