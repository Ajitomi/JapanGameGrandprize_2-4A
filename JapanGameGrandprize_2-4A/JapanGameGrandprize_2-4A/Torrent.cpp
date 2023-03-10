#include "Torrent.h"
#include "DxLib.h"
#include "Player.h"
#include "Stage/Stage.h"

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Torrent::Torrent()
{
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Torrent::~Torrent()
{
}

//-----------------------------------
//�X�V
//-----------------------------------
void Torrent::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//�O�̍��W

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());
		break;
	case ENEMY_STATE::FALL:
		Fall();
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}
}

//-----------------------------------
//�A�C�h�����
//-----------------------------------
void Torrent::Idol()
{
}

//-----------------------------------
//�ړ�
//-----------------------------------
void Torrent::Move(const Location player_location)
{
}

//-----------------------------------
//����
//-----------------------------------
void Torrent::Fall()
{
}

//-----------------------------------
//�U��
//-----------------------------------
void  Torrent::Attack(Location player_location)
{
}

//-----------------------------------
//�U�����������Ă��邩
//-----------------------------------
AttackResource Torrent::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	return ret;
}

//-----------------------------------
//���S
//-----------------------------------
void Torrent::Death()
{
}

//-----------------------------------
//�v���C���[�̒e�Ƃ̓����蔻��
//-----------------------------------
void Torrent::HitBullet(const BulletBase* bullet)
{
}

//-----------------------------------
//�`��
//-----------------------------------
void Torrent::Draw() const
{
}

//-----------------------------------
//���W�̎擾
//-----------------------------------
Location Torrent::GetLocation() const
{
	return location;
}