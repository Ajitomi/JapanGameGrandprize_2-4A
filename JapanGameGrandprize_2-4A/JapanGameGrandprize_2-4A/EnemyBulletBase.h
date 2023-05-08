#pragma once
#include "EnumEnemyType.h"
#include "SphereCollider.h"

class EnemyBulletBase :
	public SphereCollider
{
public:
	//�R���X�g���N�^
	EnemyBulletBase();

	//�f�X�g���N�^
	~EnemyBulletBase();

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() const = 0;

	//��ʊO�ɏo�����ǂ���
	bool ScreenOut();

	//�X�e�[�W�Ƃ̓����蔻��
	bool HitStage(const class Stage* stage) const;

	//�_���[�W�̎擾
	int GetDamage() const;

	//�^�C�v�̎擾
	ENEMY_TYPE GetType() const;
protected:

	int damage; //�_���[�W
	int speed; //���x

	ENEMY_TYPE type; //����	
};