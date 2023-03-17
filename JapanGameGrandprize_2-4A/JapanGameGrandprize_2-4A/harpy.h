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
	int harpy_image; //�n�[�s�B�̉摜�B
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
	Harpy();

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