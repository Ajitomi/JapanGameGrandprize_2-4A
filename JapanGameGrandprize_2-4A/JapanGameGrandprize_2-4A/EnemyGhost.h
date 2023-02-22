#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"
#include"Stage/Stage.h"
#include"GhostBullet.h"

enum class GHOST_STATE
{
	NORMAL,   //�ʏ�ړ�
	LEFT_lOWER,   //�����Ɉړ�
	LEFT_UPPER,   //����Ɉړ�
	RIGHT_LOWER,  //�E���Ɉړ�
	RIGHT_UPPER,  //�E��Ɉړ�
};

enum class GHOST_ATTACK
{
	PHYSICAL_ATTACK = 0, //�����U��
	MAGIC_ATTACK, //���@�U��
	NONE
};

class EnemyGhost : public EnemyBase, public BoxCollider
{
private:

	int standby_time; //�d������
	float player_x; //�v���C���[�̍��W��ۑ�
	float player_y; //�v���C���[�̍��W��ۑ�
	bool magic_attack; //���@�U��
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	bool setting; //�e�ۏ�������
	GHOST_STATE action_type; //�s���p�^�[��
	GHOST_ATTACK attack_state; //�U�����
	GhostBullet* bullet; //�e
public:

	EnemyGhost(); //�R���X�^���N�^

	//�`��ȊO�̍X�V�����s
	void Update()override;

	//�`��
	void Draw()const override;

	//�A�C�h�����
	void Idol() override;

	//�ړ�
	void Move(const Location player_location) override;

	//�U��
	AttackResource Attack(const BoxCollider* collider) override;

	//���S
	void Death() override;

	//�S�[�X�g�̓��������߂�
	void GhostMove(Player* player);

	//�v���C���[�̒e�ۂƂ̓����蔻��
	void HitBullet(BulletBase* bullet);
};
