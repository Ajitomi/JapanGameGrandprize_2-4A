#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class SLIME_ATTACK
{
	BEFORE_ATTACK,//�U������O
	AFTER_ATTACK,//�U��������
};

class EnemySlime :
	public EnemyBase
{
private:
	bool attack; //�U��������������

	SLIME_ATTACK slime_attack;

	int image_type;
	int image_change_time;
	int image_addition;
	int slime_angle;
	int wait_time;

	Location jump_distance;

public:

	EnemySlime(Location);
	~EnemySlime();

	//�`��ȊO�̍X�V�����s
	virtual void Update(const class Player* player, const class Stage* stage)override;
	//�`��
	virtual void Draw()const override;

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

	virtual void HitBullet(const BulletBase* bullet)override;

	//���W�̎擾
	Location GetLocation() const override;
};