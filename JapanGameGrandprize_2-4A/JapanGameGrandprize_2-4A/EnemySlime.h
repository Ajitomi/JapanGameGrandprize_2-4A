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
	int poisonsound;//�ł̒e
	int slimeataack;//�X�^�C���̓�����
	Location jump_distance;
private:
#ifdef _DEBUG
	ENEMY_STATE old_state; //��O�̏��
	int attack_time; //�U���̎���
	Location debug_location; //�f�o�b�N�p�̍��W
#endif // _DEBUG

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
	void  Attack(const Location) override;

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