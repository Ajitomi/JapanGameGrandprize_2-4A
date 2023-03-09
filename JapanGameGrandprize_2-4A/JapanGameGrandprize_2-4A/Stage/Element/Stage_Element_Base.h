#pragma once
#include "../Define.h"

class Player;
class MapChip;

class Stage_Element_Base
{
private:


protected:
	
	MapChip* mapchip;
	int image;
	

public:
	
	//�f�t�H���g�R���X�g���N�^
	Stage_Element_Base();

	//�R���X�g���N�^
	Stage_Element_Base(MapChip* mapchip, int image);
	//�R���X�g���N�^
	//Stage_Element(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~Stage_Element_Base();
	//�X�V
	virtual void Update(Player* player) = 0;
	//�`��
	virtual void Draw() const = 0;

	/// <summary>
	/// �v���C���[�ƃu���b�N���������Ă��邩��Getter
	/// </summary>
	bool HitPlayer(Player* player) const;
};