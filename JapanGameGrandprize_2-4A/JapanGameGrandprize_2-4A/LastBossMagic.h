#pragma once
#include "EnemyBulletBase.h"

class LastBossMagic :
    public EnemyBulletBase
{
private:

	bool standby; //�X�^���o�C
	bool can_delete; //�폜�\
	int* images; //�摜
	int image_num; //�摜�̖���
	double size; //�傫��
	double image_size; //�摜�̑傫��
	int angle; //�p�x
	int standby_time; //��������
	int magic_circle_image; //���@�w�̉摜
	int animation; //�A�j���[�V����

	int argument; //�摜�̈���
public:
	//�R���X�g���N�^
	LastBossMagic();

	//�R���X�g���N�^
	LastBossMagic(const Location);

	//�f�X�g���N�^
	~LastBossMagic();

	//�X�V
	void Update() override;

	//�`��
	void Draw() const override;

	//�폜�\�t���O�̎擾
	bool GetCanDelete() const;

	//�X�^���o�C��Ԃ̎擾
	bool GetDoStandby() const;
};

