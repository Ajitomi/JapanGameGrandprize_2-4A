#pragma once

class Player;

class Element_Wooden_Floor
{
private:

	//�I�u�W�F�N�g
	Player* player;

public:

	//�R���X�g���N�^
	Element_Wooden_Floor();
	//�f�X�g���N�^
	~Element_Wooden_Floor();
	//�X�V
	void Update(Player* player);
	//�`��
	void Draw() const;


};