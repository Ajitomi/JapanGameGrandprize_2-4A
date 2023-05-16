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
	CHARGE = 0,	//�`���[�W
	FALL,		//����
	LANDING,	//���e
};

class LastBossSpecialMoves
{
private:
	bool end; //�I��
	int tick; //�X�V
	Effect* effect; //�G�t�F�N�g
	Effect* charge_effect; //�`���[�W�G�t�F�N�g
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
	bool GetEnd() const;

	//�`���[�W�I��
	bool EndCharge() const;
};

