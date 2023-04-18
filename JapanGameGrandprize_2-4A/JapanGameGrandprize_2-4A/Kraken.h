#pragma once
#include "EnemyBase.h"


enum class KRAKEN_STATE
{
	NORMAL,   //�ʏ�ړ� 
	NONE //�����s�����Ȃ��B
};

enum class KRAKEN_ATTACK
{
	NONE = 0,  //�U�������Ă��Ȃ��B
	TENTACLE_ATTACK, //�G��U��
	BREATH, //�u���X�U��(�������j
	HARD_ATTACK, //���̉�𗎂Ƃ�
	
};

class Kraken :
    public EnemyBase
{
private:

	KRAKEN_ATTACK attack_state;

public:

	//�R���X�g���N�^
	Kraken(Location);

	//�f�X�g���N�^
	~Kraken();

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

	//�������U���i���̉�𗎂Ƃ��j
	void AttackWater(const Location player_location);

	//����
	void Fall() override;

	//�U��
	void  Attack(const Location) override;

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
