#pragma once
#include"EnemyBase.h"

enum class KRAKEN_TENTACLE
{
	NONE = 0,  //�U�������Ă��Ȃ��B
	TENTACLE_ATTACK, //�G��U��
};

class KrakenTentacle :public EnemyBase
{
private:

	int image;
	int time; //�U���J�n�𑪂�


	float old_x;
	bool go_back; //�Â����W�ɖ߂�
	bool attack_state; //�U���J�n
	bool attack;

	KRAKEN_TENTACLE attack_move;

public:
	//�R���X�g���N�^
	KrakenTentacle(Location);

	//�f�X�g���N�^
	~KrakenTentacle();

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

