#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"

enum class Ghost_STATE
{
	IDOL,   //�ʏ�ړ�
	lOWER_LEFT,   //����
	ATTACK,   //�U��
	DEATH,   //���S
};


class EnemyGhost : public EnemyBase, public BoxCollider
{
private:

	int action_time; //�s������
	int action_type; //�s���p�^�[��
	bool ghost_death; //�S�[�X�g���|���ꂽ��true
	bool ghost_vanish; //�S�[�X�g��������������true

public:

	EnemyGhost(); //�R���X�^���N�^

	//�`��ȊO�̍X�V�����s
	void Update()override;

	//�`��
	void Draw()const override;

	void GhostAttack(); //�S�[�X�g�̃A�^�b�N����

	void GhostMove(Player* player);

	void HitBullet(Bullet* bullet);

	bool GhostRange();
};
