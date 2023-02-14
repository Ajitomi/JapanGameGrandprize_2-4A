#pragma once
#include "Define.h"
#include "Bullet.h"

//�G�l�~�[�̎��
enum class ENEMY_KIND
{
	/*�G���G*/
	SLIME = 0,	//�X���C��
	UNDEAD,		//�A���f�b�g
	HARPY,		//�n�[�s�B
	MAGE,		//���C�W
	GHOST,		//�S�[�X�g
	WYVERN,		//���C�o�[��

	/*�{�X*/
	KING_SLIME, //�X���C���L���O
	TORRENT,	//�g�����g
	GARGOYLE,	//�K�[�S�C��
	DRAGON,		//�h���S��
	END_BOSS,	//���X�{�X
	NONE
};

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

class EnemyBase
{
public:
	//�R���X�g���N�^
	EnemyBase() {};

	//�f�X�g���N�^
	~EnemyBase() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update() = 0;

	//�`��
	virtual void Draw() const = 0;

	//HP��0���ǂ������f(0�ɂȂ�����true)
	bool CheckHp();

	//�v���C���[�̒e�Ƃ̓����蔻��
	virtual void HitBullet(Bullet* bullet) = 0;

	//�h���b�v�A�C�e���̎擾
	ElementItem GetDropItem() const;

	//�G�l�~�[�̎�ނ̎擾
	ENEMY_KIND GetEnemyKind() const;

protected: 
	int hp;	//�̗�
	int speed; //�ړ����x

	ElementItem drop_item; //�h���b�v�A�C�e��

	ENEMY_KIND kind; //�G�l�~�[�̎��
	ENEMY_TYPE* type; //�G�l�~�[�̃^�C�v

protected:
	//�h���b�v�A�C�e���̐ݒ�
	ElementItem DropItem(ENEMY_TYPE enemy_type, int min_drop, int max_drop);
};