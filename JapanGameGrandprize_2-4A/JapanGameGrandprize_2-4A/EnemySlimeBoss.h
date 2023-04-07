//#pragma once
//
//#include"SlimeBossBody.h"
//#include"EnemyBase.h"
//
//#define BODY_MAX 30
//#define DATA 100
//
//class EnemySlimeBoss : public EnemyBase
//{
//private:
//
//	Location location_data[DATA];
//	ENEMY_STATE state;
//	SlimeBossBody* slime_boss_body[BODY_MAX];
//
//public:
//
//	EnemySlimeBoss();
//	~EnemySlimeBoss(){};
//
//	//�`��ȊO�̍X�V�����s
//	virtual void Update(const Stage* stage, const Player* player);
//	//�`��
//	virtual void Draw()const;
//};

#pragma once

#define BODY_MAX 30
#define DATA 100

#include"EnemyBase.h"
#include"SlimeBossBody.h"

class EnemySlimeBoss : public EnemyBase
{
private:

	Location location_data[DATA];
	ENEMY_STATE state;
	SlimeBossBody* slime_boss_body[BODY_MAX];
	int slime_boss_jump_distance;
	int speed_y;

#ifdef _DEBUG
	ENEMY_STATE old_state; //��O�̏��
	Location debug_location; //�f�o�b�N�p�̍��W
#endif // _DEBUG

public:

	EnemySlimeBoss(Location spawn_location);
	~EnemySlimeBoss();

	//�`��ȊO�̍X�V�����s
	virtual void Update(const Player* player, const Stage* stage)override;
	//�`��
	virtual void Draw()const override;

	//�ړ�
	void Move(const Location player_location) override;

	//����
	void Fall() override;

	void Idol() override;

	//�U��
	void  Attack(Location) override;

	//�U�����������Ă��邩
	AttackResource Hit() override;

	//���S
	void Death() override;

	virtual void HitBullet(const BulletBase* bullet)override;

	//���W�̎擾
	Location GetLocation() const override;

#ifdef _DEBUG
	//�X�V(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//�`��(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};