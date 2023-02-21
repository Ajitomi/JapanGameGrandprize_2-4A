#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "EnumEnemyType.h"

//�e�����̃h���b�v��
#define FIRE_DROP 3
#define WATER_DROP 4
#define WIND_DROP 3
#define SOIL_DROP 4
#define THUNDER_DROP 7

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



class EnemyBase
{
public:
	//�R���X�g���N�^
	EnemyBase();

	//�f�X�g���N�^
	~EnemyBase() {}

	//�`��ȊO�̍X�V�����s
	virtual void Update() = 0;

	//�`��
	virtual void Draw() const = 0;

	//�v���C���[�̒e�Ƃ̓����蔻��
	virtual void HitBullet(Bullet* bullet) = 0;

	//�h���b�v�����ނ̗ʂ̎擾
	int GetDropTypeVolume() const;

	//�h���b�v����A�C�e���̗ʂ̎擾
	int GetDropVolume()const;

	//�h���b�v�A�C�e���̎擾
	ElementItem GetDropItem(int i) const;

	//�G�l�~�[�̎�ނ̎擾
	ENEMY_KIND GetEnemyKind() const;

	//�폜�\��Ԃ̎擾
	bool GetCanDelete() const;

protected:
	bool can_delete; //�폜�t���O
	int hp;	//�̗�
	int speed; //�ړ����x

	int drop_volume; //�h���b�v��
	int drop_type_volume; //�h���b�v�����ނ̗�

	ElementItem** drop_element; //�h���b�v���f

	ENEMY_KIND kind; //�G�l�~�[�̎��
	ENEMY_TYPE* type; //�G�l�~�[�̃^�C�v
protected:
	//HP��0���ǂ������f(0�ɂȂ�����true)
	bool CheckHp();
};