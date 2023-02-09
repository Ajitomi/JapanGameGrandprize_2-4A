#pragma once
#include"EnemyBase.h"
class EnemyGhost : public EnemyBase
{
private:

	int ghost_x; //�S�[�X�g��X���W
	int ghost_y; //�S�[�X�g��Y���W
	int action_time; //�s������
	int action_type; //�s���p�^�[��
	bool ghost_lost; //�S�[�X�g���|���ꂽ��true
	bool ghost_hide; //�S�[�X�g��������������true

public:

	EnemyGhost(); //�R���X�^���N�^

	//�`��ȊO�̍X�V�����s
	void Update()override;

	//�`��
	void Draw()const override;

	void GhostAttack(); //�S�[�X�g�̃A�^�b�N����

	void GhostMove();  //�S�[�X�g�̓���
};
