#pragma once

#include"EnemyBase.h"
#include"CameraWork.h"
#include"SlimeBossBullet.h"

enum class MOVE_STATE
{
	MOVE,
	WALL_MOVE
};

class EnemySlimeBoss : public EnemyBase
{
private:

	ENEMY_STATE state;
	MOVE_STATE move_state;
	int slime_boss_jump_distance;
	int speed_y;
	int wait_time;
	int breath_time;

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

	void MagicBullet(const Location player_location);

#ifdef _DEBUG
	//�X�V(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//�`��(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};