#pragma once
#include "Stage_Element_Base.h"
class Element_Fall_Floor : public Stage_Element_Base
{
private:
	

	//�_��
	bool is_flash;

	//�����X�s�[�h
	float fall_speed;
	
	enum class STATE {
		NONE,		//�Ȃ�
		WORKING,	//������O
		FALL,		//����
	} state;

public:

	//�R���X�g���N�^
	Element_Fall_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	//�f�X�g���N�^
	~Element_Fall_Floor();
	//�X�V
	void Update(Player* player) override;



};