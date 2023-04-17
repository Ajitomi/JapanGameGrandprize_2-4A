#pragma once
#include "EnemyBase.h"
#include"BoxCollider.h"
#include"DragonBullet.h"
#include"DragonThunder.h"

enum class DRAGON_STATE
{
	NORMAL,   //�ʏ�ړ� 
	NONE //�����s�����Ȃ��B
};

enum class DRAGON_ATTACK
{
	DITE = 0, //���݂�
	TAIL_ATTACK, //�K���̍U��
	DREATH, //�u���X�U��(�Α����j
	ROAR, //���K������ɁA�����~�点��
	NONE //�U�������Ă��Ȃ��B
};

class Dragon :public EnemyBase
{
private:
	int image;
	int animation; //�摜�̃A�j���[�V����
	int magic_num; //�������U�����g������
	int attack_method; //�U�����@
	int switchover_time; //�U���؂�ւ�����
	int breath_time; //�u���X���ˊԊu�B
	int effect_time; //�ł̃_���[�W�𓙊Ԋu�ŏo�����߂̎��ԑ���
	int standby_time; //�ҋ@���ԑ���
	int animation_time; //	�摜�؂�ւ��Ԋu
	int fall_speed; //�������x
	int ascent_time; //�㏸����
	int fly_tim; //�Q�[�����̃J�E���g
	int fly_num; //��ё����鎞��
	
	float old_x; //�ڕW�n�_
	float old_y; //�ړI�n�_
	float player_x; //�Â����W
	float player_y; //�Â����W

	bool attack_tail; //�K���U����
	bool set_coordinate; //�K���U���i�v���C���[�̏ꏊ�ɍs���j
	bool wall_hit; //�ǂɓ��������̂��B
	bool attack; //�ڋߍU��
	bool magic; //���@�U��


	DRAGON_ATTACK attack_state; //�U�����

public:

	//�R���X�g���N�^
	Dragon(Location);

	//�f�X�g���N�^
	~Dragon();

	//�`��ȊO�̍X�V�����s
	void Update(const class Player* player, const class Stage* stage)override;

	//�`��
	void Draw()const override;

	//�A�C�h�����
	void Idol() override;

	//�ړ�
	void Move(const Location player_location) override;

	//�ڋߍU���i���݂��j���̓���
	void DiteMove(const Location player_location);

	//�������U���i�u���X�j���̓���
	void DreathMove(const Location player_location);

	//�������U���i���K������ɗ����L�͈͂ɍ~�点��j���̓���
	void RoarMove(const Location player_location);

	//����
	void Fall() override;

	//���
	void Fly();

	//�U��
	void  Attack(const Location player_location) override;

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

