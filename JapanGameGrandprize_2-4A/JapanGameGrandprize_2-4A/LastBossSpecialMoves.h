#pragma once
#include "Define.h"

//�G�t�F�N�g
struct Effect
{
	bool draw; //�`�悷��
	Location location; //���W
	int* images; //�摜
	int animation; //�A�j���V����
	double size; //�傫��
	double angle; //�p�x
	int alpfa_brend; //�����x
};

enum class SPECIAL_MOVES_STATE
{
	FALL = 0,	//����
	LANDING,	//���e
};

class LastBossSpecialMoves
{
private:
	int end; //�I��
	int tick; //�X�V
	Effect* effect; //�G�t�F�N�g
	SPECIAL_MOVES_STATE state; //���
public:
	//�R���X�g���N�^
	LastBossSpecialMoves(const Location);

	//�f�X�g���N�^
	~LastBossSpecialMoves();

	//�X�V
	void Update();

	//�`��
	void Draw() const;

	//�_���[�W�̎擾
	int GetDamage() const;

	//�I�����̎擾
	int GetEnd() const;
};

