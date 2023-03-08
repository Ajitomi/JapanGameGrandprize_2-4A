#pragma once

class Stage_Element_Base
{
private:


protected:
	const int *image;
	

public:
	
	//�R���X�g���N�^
	Stage_Element_Base();
	//�R���X�g���N�^
	//Stage_Element(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~Stage_Element_Base();
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Draw() const = 0;
};