#include "DxLib.h"
#include "Torrent.h"


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Torrent::Torrent(Player* player)
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
void Torrent::Update()
{

}

//-----------------------------------
//�U��
//-----------------------------------
AttackResource Torrent::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //�߂�l

	return ret;
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
//��Ԃ̎擾
//-----------------------------------
TORRENT_STATE Torrent::GetState() const
{
	return state;
}