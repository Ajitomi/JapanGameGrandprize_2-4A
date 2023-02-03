#pragma once

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
	GOLEM,		//�S�[����
	DRAGON,		//�h���S��
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
	EnemyBase();

	//�f�X�g���N�^
	~EnemyBase() {};

	//�`��ȊO�̍X�V�����s
	virtual void Update() = 0;

	//�`��
	virtual void Draw() const = 0;

	//HP��0���ǂ������f(0�ɂȂ�����true)
	bool CheckHp()
	{
		bool ret = false;
		if (hp < 0)
		{
			ret = true;
		}
		return ret;
	}

protected:
	int hp;	//�̗�
	int speed; //�ړ����x

	ENEMY_KIND kind; //�G�l�~�[�̎��
	ENEMY_TYPE type; //�G�l�~�[�̃^�C�v
};

