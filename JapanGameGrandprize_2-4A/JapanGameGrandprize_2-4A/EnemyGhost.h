#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"
#include"Stage/Stage.h"

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
	int ghost_hp; //�S�[�X�g��HP
	float bullet_x; //�e��
	float bullet_y; //�e��
	float bullet_speed_x; //�e�ۃX�s�[�h
	float bullet_speed_y; //�e�ۃX�s�[�h
	float player_x; //�v���C���[�̍��W��ۑ�
	float player_y; //�v���C���[�̍��W��ۑ�
	bool magic_attack; //���@�U��
	bool ghost_vanish; //�S�[�X�g��������������true
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	bool setting; //�e�ۏ�������
	GHOST_STATE action_type; //�s���p�^�[��

public:

	EnemyGhost(); //�R���X�^���N�^

	//�`��ȊO�̍X�V�����s
	void Update()override;

	//�`��
	void Draw()const override;

	//�S�[�X�g�̃A�^�b�N����
	void GhostAttack();

	//�S�[�X�g�̓��������߂�
	void GhostMove(Player* player);

	//�v���C���[�̒e�ۂƂ̓����蔻��
	void HitBullet(Bullet* bullet);


};
