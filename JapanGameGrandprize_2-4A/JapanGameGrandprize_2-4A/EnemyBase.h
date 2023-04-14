#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "EnumEnemyType.h"
#include "BoxCollider.h"
#include "Stage/Stage.h"

//�e�����̃h���b�v��
#define FIRE_DROP 4
#define WATER_DROP 4
#define WIND_DROP 4
#define SOIL_DROP 4
#define THUNDER_DROP 7

//�_���[�W�{��
#define WEAKNESS_DAMAGE 2.0f
#define RESISTANCE_DAMAGE 0.5f

//�f�o�t�̌��ʎ��Ԃ̔{��
#define WEAKNESS_DEBUFF 1.5f
#define	RESISTANCE_DEBUFF 0.5f

//�Ń_���[�W���󂯂�܂ł̃t���[����
#define POISON_DAMAGE_FLAME 10

//��჏�Ԃ̈ړ��X�s�[�h�̔{��
#define PARALYSIS_SPEED 0.5f

//�������x
#define ENEMY_FALL_SPEED 1

//�_���[�W���O�̐�
#define LOG_NUM 3

//���O�̕`�掞��
#define LOG_TIME 60

//���O��Y���W
#define LOG_Y 20

//�����蔻��
struct HitMapChip
{
	bool hit; //����������
	MapChip* chip; //�}�b�v�`�b�v
};

//�_���[�W����
enum class CONGENIALITY
{
	WEAKNESS = 0,	//��_
	NOMAL,			//�ʏ�
	RESISTANCE,		//�ϐ�
	INVALID,		//����
};

//�X�e�[�W�u���b�N�Ɠ���������
enum class STAGE_DIRECTION
{
	TOP,	//���
	BOTTOM,	//����
	LEFT,	//����
	RIGHT	//�E��
};

//�G�l�~�[�̎��
enum class ENEMY_KIND
{
	/*�G���G*/
	SLIME = 200,	//�X���C��
	UNDEAD,		//�A���f�b�g
	HARPY,		//�n�[�s�B
	MAGE,		//���C�W
	GHOST,		//�S�[�X�g
	WYVERN,		//���C�o�[��

	/*�{�X*/
	SLIME_BOSS, //�X���C���L���O
	TORRENT,	//�g�����g
	KRAKEN,	    //�N���[�P��
	DRAGON,		//�h���S��
	END_BOSS,	//���X�{�X
	NONE
};

//�G�l�~�[�̏��
enum class ENEMY_STATE
{
	IDOL,   //�A�C�h�����
	MOVE,   //�ړ�
	FALL,	//����
	ATTACK, //�U��
	DEATH,  //���S
};

struct DamageLog
{
	bool log; //���O�̕\��
	int damage; //�_���[�W
	int time; //�`�掞��
	CONGENIALITY congeniality; //����
};

class EnemyBase :
	public BoxCollider
{
public:

	//�R���X�g���N�^
	EnemyBase();

	//�f�X�g���N�^
	~EnemyBase() {}

	//�X�V
	virtual void Update(const class Player* player, const class Stage* stage) = 0;

	//�`��
	virtual void Draw() const = 0;

	//HP�o�[�̕`��
	virtual void DrawHPBar(const int) const;

	//�_���[�W���O�̕`��
	virtual void DrawDamageLog() const;

	//�_���[�W���O�̍X�V
	virtual void UpdateDamageLog();

	//�A�C�h�����
	virtual void Idol() = 0;

	//�ړ�
	virtual void Move(const Location player_location) = 0;

	//����
	virtual void Fall() = 0;

	//�U��
	virtual void  Attack(const Location) = 0;

	//�U�����������Ă��邩
	virtual AttackResource Hit() = 0;

	//�X�e�[�W�Ƃ̓����蔻��
	HitMapChip HitStage(const class Stage* stage);

	//�X�e�[�W�̂ǂ̖ʂƓ��������𔻒f
	STAGE_DIRECTION HitDirection(const class MapChip* map_chip);

	//���S
	virtual void Death() = 0;

	//�v���C���[�̒e�Ƃ̓����蔻��
	virtual void HitBullet(const BulletBase* bullet) = 0;

	//�h���b�v�����ނ̗ʂ̎擾
	int GetDropTypeVolume() const;

	//�h���b�v����A�C�e���̗ʂ̎擾
	int GetDropVolume()const;

	//�h���b�v�A�C�e���̎擾
	ElementItem GetDropItem(int i) const;

	//�G�l�~�[�̎�ނ̎擾
	ENEMY_KIND GetEnemyKind() const;

	//�G�l�~�[�̏�Ԃ̎擾
	ENEMY_STATE GetState()const;

	//�폜�\��Ԃ̎擾
	bool GetCanDelete() const;

	//���W�̎擾
	virtual Location GetLocation() const = 0;

	//���O�p�̃t�H���g�̍쐬
	static void CreateLogFont();

	//���O�p�̃t�H���g�̍폜
	static void DeleteLogFont();
#ifdef _DEBUG
	//�X�V(DotByDot)
	virtual void Update(const ENEMY_STATE state) = 0;

	//�`��(DotByDot)
	virtual void DebugDraw() = 0;
#endif // _DEBUG
protected:

	bool can_delete; //�폜�t���O
	bool left_move; //���ɓ����Ă��邩�ǂ���
	bool poison;	//�ŏ��
	bool paralysis; //��჏��
	int damage;		//�_���[�W
	int* images; //�摜
	int hp;	//�̗�
	int speed; //�ړ����x
	int poison_time; //�ł̌��ʎ���
	float poison_damage; //�ł̃_���[�W
	int paralysis_time; //��Ⴢ̌��ʎ���
	static int log_font[4]; //�����p�̃t�H���g(0:��_,1:�ʏ�,2:�ϐ�,3:��_,)
	int drop_volume; //�h���b�v��
	int drop_type_volume; //�h���b�v�����ނ̗�
	ElementItem** drop_element; //�h���b�v���f

	ENEMY_KIND kind; //�G�l�~�[�̎��
	ENEMY_TYPE* type; //�G�l�~�[�̃^�C�v
	ENEMY_STATE state; //�G�l�~�[�̏��
	DamageLog damage_log[LOG_NUM]; //�_���[�W���O
protected:

	//�_���[�W���O�̏�����
	void InitDamageLog();

	//HP��0���ǂ������f(0�ɂȂ�����true)
	bool CheckHp();

	//��ʊO�ɏo��
	bool ScreenOut();

	//�ŏ�Ԃ̏���
	void Poison();

	//��჏�Ԃ̏���
	void Paralysis();
};