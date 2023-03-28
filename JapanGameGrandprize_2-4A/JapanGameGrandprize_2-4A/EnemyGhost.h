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
	int ghost_image[7]; //�S�[�X�g�̉摜�B
	int animation; //�A�j���[�V����
	int animation_time; //�A�j���[�V�����̎���
	int physical_time; //�����U������
	int magic_num; //���@�U��������
	int magic_time; //���@�U������
	float speed; //�S�[�X�g�̈ړ����x
	float travel; //X���W�ɓ�����
	float travel_y; //�����W�ɓ�����
	float range; //�v���C���[�Ƃ̋���	
	float range_y; //�v���C���[�Ƃ̋���Y��
	float vector; //�x�N�g��
	bool magic_attack; //���@�U��
	bool attack; //�U��������������
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	bool hit_ground; //�n�ʂƂ̓����蔻��
	GHOST_STATE action_type; //�s���p�^�[��
	GHOST_ATTACK attack_state; //�U�����
public:

	//�R���X�^���N�^
	EnemyGhost(Location);

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

	//�ڋߍU��
	void AttackMove(const Location player_location);

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