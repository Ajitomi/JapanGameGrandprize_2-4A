#pragma once

#include"EnemyBase.h"
#include"CameraWork.h"

#include"SlimeBossBullet.h"
#include"SlimeBossThunder.h"


enum class ATTACKTYPE
{
	NONE,
	MAGIC_BULLET,
	THUNDER
};

class EnemySlimeBoss : public EnemyBase
{
private:

	int slime_boss_image;
	int slime_boss_jump_distance;
	int speed_y;
	int wait_time;
	int cloud_move_time;
	int cloud_brightness;
	int magic_circle_image;

	void DrawHPBar(const int) const;//hp�o�[�\��

	ENEMY_STATE now_state;
	Location cloud_location;

	ATTACKTYPE attack_type;

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
	void Update_Cloud(const Player* player);

	void Draw_Cloud()const;

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
	void Thunder(const Location player_location);


#ifdef _DEBUG
	//�X�V(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//�`��(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};