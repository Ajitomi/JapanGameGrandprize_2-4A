#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"


class SlimeBossBody: public EnemyBase
{
private:

	bool attack; //�U��������������
	STAGE_DIRECTION hit_direction_all;

#ifdef _DEBUG
	ENEMY_STATE old_state; //��O�̏��
	Location debug_location; //�f�o�b�N�p�̍��W
#endif // _DEBUG

public:

	SlimeBossBody(int x, int y);
	~SlimeBossBody();

	//�`��ȊO�̍X�V�����s
	virtual void Update(const class Player* player, const class Stage* stage)override;
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

	void SetLocation(Location location);

	void WalkWall();

#ifdef _DEBUG
	//�X�V(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//�`��(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};












