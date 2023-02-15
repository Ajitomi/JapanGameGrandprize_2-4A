#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"

enum class GHOST_STATE
{
	NORMAL,   //�ʏ�ړ�
	LEFT_lOWER,   //�����Ɉړ�
	LEFT_UPPER,   //����Ɉړ�
	RIGHT_LOWER,  //�E���Ɉړ�
	RIGHT_UPPER,  //�E��Ɉړ�
	PHYSICAL_ATTACK,       //�����U��
	MAGIC_ATTACK, //���@�U��
	DEATH,   //���S
};


class EnemyGhost : public EnemyBase, public BoxCollider
{
private:

	int standby_time; //�d������
	bool magic_attack; //���@�U��
	bool ghost_vanish; //�S�[�X�g��������������true
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	GHOST_STATE action_type; //�s���p�^�[��

public:

	EnemyGhost(); //�R���X�^���N�^

	//�`��ȊO�̍X�V�����s
	void Update()override;

	//�`��
	void Draw()const override;

	void GhostAttack(); //�S�[�X�g�̃A�^�b�N����

	void GhostMove(Player* player);

	void HitBullet(Bullet* bullet);

};
