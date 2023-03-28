#pragma once
#include "EnemyBase.h"
#include"BoxCollider.h"
#include"HarpyBullet.h"

enum class HARPY_STATE
{
	NORMAL,   //�ʏ�ړ� ���Ɉړ�
	NORMAL_RIGHT, //�ʏ�ړ� �E�Ɉړ�
	NONE //�����s�����Ȃ��B
};

enum class HARPY_ATTACK
{
	PHYSICAL_ATTACK = 0, //�����U��
	MAGIC_ATTACK, //���@�U��
	NONE //�U�������Ă��Ȃ��B
};

class Harpy :public EnemyBase
{
private:

	int standby_attack; //���̍U���ҋ@����
	int standby_time; //�d������
	int magic_num; //���@�U��������
	int harpy_image; //�n�[�s�B�̉摜
	int magic_time; //���@�U���̊Ԋu�B�W
	float vector; //�x�N�g��
	int physical_time; //�����U������
	float range; //�v���C���[�Ƃ̋���	
	float range_y; //�v���C���[�Ƃ̋���Y��
	float travel; //X���W�ɓ�����
	float travel_y; //�����W�ɓ�����
	bool magic_attack; //���@�U��
	bool attack; //�U��������������
	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
	bool inversion; //���]�i�ǂɂ���������)
	HARPY_STATE action_type; //�s���p�^�[��
	HARPY_ATTACK attack_state; //�U�����
public:

	//�R���X�^���N�^
	Harpy(Location);

	//�f�X�g���N�^
	~Harpy();

	//�`��ȊO�̍X�V�����s
	void Update(const class Player* player, const class Stage* stage)override;

	//�`��
	void Draw()const override;

	//�A�C�h�����
	void Idol() override;

	//�ړ�
	void Move(const Location player_location) override;

	//�ڋߍU���i�����U���j���̓���
	void PhysicalMove(const Location player_location);

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

#ifdef _DEBUG
	//�X�V(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//�`��(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG

};