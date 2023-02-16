#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "Item.h"

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

	//�v���C���[�̒e�Ƃ̓����蔻��
	virtual void HitBullet(Bullet* bullet) = 0;

	//�h���b�v�A�C�e���̎擾
	ElementItem GetDropItem(int i) const;

	//�G�l�~�[�̎�ނ̎擾
	ENEMY_KIND GetEnemyKind() const;

protected: 
	int hp;	//�̗�
	int speed; //�ړ����x

	int drop_volume; //�h���b�v��

	ElementItem** drop_element; //�h���b�v���f
	Item** drop_item; //�h���b�v�A�C�e��

	ENEMY_KIND kind; //�G�l�~�[�̎��
	ENEMY_TYPE* type; //�G�l�~�[�̃^�C�v
protected:
	//HP��0���ǂ������f(0�ɂȂ�����true)
	bool CheckHp();

	//�A�C�e���̐���
	void CreateDropItem(int drop_num, Location location);

	//�A�C�e���̕��ёւ�
	void SortDropitem(int item_num);
};