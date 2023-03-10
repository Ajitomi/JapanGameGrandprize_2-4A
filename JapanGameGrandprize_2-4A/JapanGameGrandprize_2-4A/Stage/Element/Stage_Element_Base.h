#pragma once
#include "../Define.h"
#include <memory>
#include <vector>
#include "../MapChip.h"

class Player;


class Stage_Element_Base : public MapChip
{
private:


protected:

	short type;
	std::vector<std::shared_ptr<Stage_Element_Base>> element;
	MapChip* mapchip;


public:

	//�f�t�H���g�R���X�g���N�^
	Stage_Element_Base();

	//�R���X�g���N�^
	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//�R���X�g���N�^
	//Stage_Element(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~Stage_Element_Base();
	//�X�V
	virtual void Update(Player* player) {};
	////�`��
	//virtual void Draw() const {};

	/// <summary>
	/// �X�e�[�W�v�f�̎�ނ�Getter
	/// </summary>
	short GetType() const { return type; }

	/// <summary>
	/// MapChip�I�u�W�F�N�g��Getter
	/// </summary>
	MapChip* GetMapChip() const { return mapchip; }

	/// <summary>
	/// �v���C���[�ƃu���b�N���������Ă��邩��Getter
	/// </summary>
	bool HitPlayer(Player* player) const;

	/// <summary>
	/// �X�e�[�W�v�f�̌���
	/// </summary>1
	std::shared_ptr<Stage_Element_Base> SearchElement(short type);
};