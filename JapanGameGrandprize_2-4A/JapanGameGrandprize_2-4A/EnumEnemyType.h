#pragma once

//����
enum class ENEMY_TYPE
{
	NORMAL = 0,	//������
	FIRE,		//�Α���
	WATER,		//������
	WIND,		//������
	SOIL,		//�y����
	THUNDER,	//������
};

struct AttackResource
{
	int damage; //�_���[�W
	ENEMY_TYPE* type; //�U���^�C�v
	int type_count; //�U���^�C�v�̐�
};