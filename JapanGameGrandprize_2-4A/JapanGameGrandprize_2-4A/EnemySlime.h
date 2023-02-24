#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class DIRECTION
{
	LEFT = 0,
	RIGHT
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	DIRECTION direction;

	int slime_image;
	int slime_angle;

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
	AttackResource Attack(const BoxCollider* collider) override;

	//���S
	void Death() override;

	void HitStage();

	void KnockBack();

	virtual bool HitBullet(const BulletBase* bullet)override {
		bool ret = false; //�߂�l

		return ret;
	};

	//���W�̎擾
	Location GetLocation() const override;
};
