#pragma once
#include "../Stage.h"

class Stage_Element :
    public Stage, public BoxCollider
{
private:


protected:


public:
	//�R���X�g���N�^
	Stage_Element();
	//�R���X�g���N�^
	Stage_Element(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~Stage_Element();
	//�X�V
	virtual void Update(Player* player) = 0;
	//�`��
	virtual void Draw() const = 0;
};