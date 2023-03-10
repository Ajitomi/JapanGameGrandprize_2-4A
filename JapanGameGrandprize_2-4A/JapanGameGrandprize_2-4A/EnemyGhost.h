#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Stage/Stage.h"
#include"GhostBullet.h"

enum class GHOST_STATE
{
	NORMAL,   //�ʏ�ړ� ���Ɉړ�
	NORMAL_RIGHT, //�ʏ�ړ� �E�Ɉړ�
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

class EnemyGhost :public EnemyBase
{
private:
	int standby_attack; //���̍U���ҋ@����
	int standby_time; //�d������
	int ghost_image; //�S�[�X�g�̉摜�B
	float speed; //�S�[�X�g�̈ړ����x
	bool magic_attack; //���@�U��
	bool attack; //�U��������������
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	GHOST_STATE action_type; //�s���p�^�[��
	GHOST_ATTACK attack_state; //�U�����
private:

	//�S�[�X�g�̓��������߂�
	void GhostMove(const Location player_location);
public:

	//�R���X�^���N�^
	EnemyGhost(); 

	//�f�X�g���N�^
	~EnemyGhost();

	//�`��ȊO�̍X�V�����s
	void Update(const class Player* player, const class Stage* stage)override;

	//�`��
	void Draw()const override;

	//�A�C�h�����
	void Idol() override;

	//�ړ�
	void Move(const Location player_location) override;

	//����
	void Fall() override;

	//�U��
	void  Attack(Location) override;

	//�U�����������Ă��邩
	AttackResource Hit() override;

	//���S
	void Death() override;

	//�v���C���[�̒e�ۂƂ̓����蔻��
	void HitBullet(const BulletBase* bullet) override;

	//���W�̎擾
	Location GetLocation() const override;

};
