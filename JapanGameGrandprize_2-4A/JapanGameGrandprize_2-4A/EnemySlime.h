#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class DIRECTION
{
	LEFT = 0,
	RIGHT
};

enum class SLIME_ATTACK
{
	BEFORE_ATTACK,//�U������O
	AFTER_ATTACK,//�U��������
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:

	int color;
	DIRECTION direction;
	SLIME_ATTACK slime_attack;

	int slime_image;
	int slime_angle;
	int wait_time;

	Location jump_distance;

	ElementItem drop_item;
public:

	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update()override;
	//�`��
	virtual void Draw()const override;

	//�A�C�h�����
	void Idol() override;

	//�ړ�
	void Move(const Location player_location) override;

	//�U��
	void  Attack(Location) override;

	//�U�����������Ă��邩
	AttackResource HitCheck(const BoxCollider* collider) override;

	//���S
	void Death() override;

	virtual bool HitBullet(const BulletBase* bullet)override;

	//���W�̎擾
	Location GetLocation() const override;
};
