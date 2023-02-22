#pragma once
#include "EnumEnemyType.h"
#include "SphereCollider.h"

class EnemyBulletBase :
	public SphereCollider

{
public:
	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() const = 0;

	//�_���[�W�̎擾
	int GetDamage() const;

	//�^�C�v�̎擾
	ENEMY_TYPE GetType() const;
protected:
	int damage; //�_���[�W
	int speed; //���x

	ENEMY_TYPE type; //����
};

