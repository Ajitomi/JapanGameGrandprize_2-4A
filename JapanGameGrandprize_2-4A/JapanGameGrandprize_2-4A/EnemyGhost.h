#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Stage/Stage.h"
#include"GhostBullet.h"

enum class GHOST_STATE
{
	NORMAL,   //�ʏ�ړ� ���Ɉړ�
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
	int standby_count; //�d���J�E���g
	bool magic_attack; //���@�U��
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	GHOST_STATE action_type; //�s���p�^�[��
	GHOST_ATTACK attack_state; //�U�����
	GhostBullet* bullet; //�e

private:
	//�S�[�X�g�̓��������߂�
	void GhostMove(const Location player_location);
public:
	//�R���X�^���N�^
	EnemyGhost(); 

	//�f�X�g���N�^
	~EnemyGhost();

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

	//�v���C���[�̒e�ۂƂ̓����蔻��
	bool HitBullet(const BulletBase* bullet) override;

	//���W�̎擾
	Location GetLocation() const override;

};
