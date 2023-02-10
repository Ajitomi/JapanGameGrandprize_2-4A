#include "Undead.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Undead::Undead()
{
	/*������*/
	kind = ENEMY_KIND::UNDEAD;
	type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;


}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Undead::~Undead()
{

}

//-----------------------------------
// �X�V
//-----------------------------------
void Undead::Update()
{
	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		break;
	case UNDEAD_STATE::MOVE:
		location.x += speed;
		break;
	case UNDEAD_STATE::ATTACK:
		break;
	case UNDEAD_STATE::DEATH:
		break;
	default:
		break;
	}
}

//-----------------------------------
// �U��
//-----------------------------------
void Undead::Attack()
{

}

//-----------------------------------
// �`��
//-----------------------------------
void Undead::Draw() const
{

}