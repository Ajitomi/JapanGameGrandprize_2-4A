#pragma once
#include"AbstractScene.h"

class GameOver :
	public AbstractScene
{
private:

public:

	//�R���X�g���N�^
	GameOver();
	//�f�X�g���N�^
	~GameOver() {};

	//�X�V
	AbstractScene* Update() override;

	//�`��
	void Draw() const override;
};