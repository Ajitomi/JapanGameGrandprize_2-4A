#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f
class Player;

class MapChip :
	public BoxCollider
{
private:

	//�������Ă������	�\����
	//X[�E:1, -��:-1], Y[��:1, ��:-1]
	POINT collision_dir;


public:

	//�R���X�g���N�^
	MapChip();
	//�R���X�g���N�^
	MapChip(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~MapChip();
	//�X�V
	void Update(Player* player);
	//�`��
	virtual void Draw() const;

	const char* GetName() { return class_name; }


	/// <summary>
	/// **�v���C���[�ƃX�e�[�W�̓����蔻��p**
	/// ���������}�b�v�`�b�v���W��Getter
	/// </summary>
	/// <returns>POINT�^(�\���̌^) X[�E:1, -��:-1], Y[��:1, ��:-1]</returns>	
	const POINT GetMapChip_Collision() {

		POINT w = collision_dir;

		collision_dir = { 0,0 };

		return w;
	}


protected:

	const char* class_name = "default";
	int image;
	Area image_size;
	float ex_rate;
};