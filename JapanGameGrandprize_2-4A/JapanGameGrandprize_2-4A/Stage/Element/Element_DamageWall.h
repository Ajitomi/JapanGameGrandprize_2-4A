#pragma once

class Player;

class Element_DamageWall
{
private:

	//�I�u�W�F�N�g
	Player* player;

public:

	//�R���X�g���N�^
	Element_DamageWall();
	//�f�X�g���N�^
	~Element_DamageWall();
	//�X�V
	void Update(Player* player);
	//�`��
	void Draw() const;


};