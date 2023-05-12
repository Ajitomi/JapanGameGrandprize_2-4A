#include "LastBossSpecialMoves.h"
#include "DxLib.h"
#include "CameraWork.h"
#define _USE_MATH_DEFINES
#include <math.h>

//�G�t�F�N�g�̐�
#define EFFECT_NUM 7

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
#define EFFECT_FALL_SPEED 3

//�_���[�W
#define SPECIAL_MOVES_DAMAGE 500
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
		effect[i].alpfa_brend = 255;
	}

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

	tick = 0;

	state = SPECIAL_MOVES_STATE::FALL;

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
			for (int j = 0; j < EFFECT_BODY_IMAGES; i++)
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
}

//-----------------------------------
//�X�V
//-----------------------------------
void LastBossSpecialMoves::Update()
{
	tick++;

	switch (state)
	{
	case SPECIAL_MOVES_STATE::FALL:
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			switch (i)
			{
			case 0: //�{��
				effect[i].location.y += EFFECT_FALL_SPEED;
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
				effect[i].location.y += EFFECT_FALL_SPEED;

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
				case 6:
					effect[i].location = effect[0].location;
					effect[i].draw = true;
					effect[i].alpfa_brend = MAX_ALPFA_BREND;
					break;
				case 4:
				case 5:
					effect[i].draw = false;
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
				effect[i].size += 0.0181;

				if (effect[i].size < 0.0000)
				{
					effect[i].draw = false;

					for (int j = 0; j < 2; j++)
					{
						effect[4 + j].draw = true;
					}
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
					effect[i].size *= 1.04;
				}

				effect[i].location.x = effect[0].location.x +
					(static_cast<double>(rand() % 40) - 20) * (effect[i].size / 3);		//-20 �` 19
				effect[i].location.y = effect[0].location.y +
					(static_cast<double>(rand() % 40) - 20) * (effect[i].size / 3);		//-20 �` 19

				break;
			case 4: //����
			case 5:
				break;
			case 6:
				effect[i].size += 1.20;

				if (effect[i].size > 1.500)
				{
					effect[i].draw = false;
				}
				break;
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
	Location draw_location = CameraWork::GetCamera();
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		if (effect[i].draw)
		{
			draw_location = effect[i].location - draw_location;	//�`����W�̌v�Z
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, effect[i].alpfa_brend);
			DrawRotaGraphF(draw_location.x, draw_location.y, effect[i].size,
				effect[i].angle, effect[i].images[effect[i].animation], TRUE, FALSE, FALSE);
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
int LastBossSpecialMoves::GetEnd() const
{
	return end;
}