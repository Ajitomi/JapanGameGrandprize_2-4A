#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "Bullet.h"
#include "Stage/Stage.h"
#include "EnemyBase.h"
#include "ElementItem.h"
#include "Pouch.h"
#include "DxLib.h"
#include "EnumEnemyType.h"
#include <vector>

#define JUMP_INERTIA 0.2
#define WARK_INERTIA 0.5
#define HP_MAX 100.f
#define HP_BAR_WIDTH 300
#define HP_BAR_HEIGHT 28
#define FUEL_MAX 100.f
#define FUEL_BAR_HEIGHT 100

#define PLAYER_IMAGES 7
#define ATTRIBUTE_IMAGES 10

#define PLAYER_SPEED_X 5.0

#define BULLET_MAX 50


enum class PLAYER_STATE
{
	STOP = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	FLY,
	DOWN,
	DEATH
};

class Player : public BoxCollider
{
private:

	int animation;					//�摜�A�j���[�V�����p
	int image_count;				//�摜�̗v�f���p
	int* image;						//�摜�p�ϐ�
	int* jump_image;				//���ł�Ƃ��̉摜
	int* attribute_images;			//�����̉摜
	int hp_image;
	int image_size_x, image_size_y; //�摜�̃T�C�Y
	int hp;							//�̗�
	int bullet_count;				//�������e�̐�
	int shoot_count;                //�������J�E���g����


	float jump_power;				//�W�����v�̃p���[
	int jump_bottun_count;			//�W�����v�{�^������͂��Ă��鎞�Ԃ𐔂���	
	int not_jet_count;              //����łȂ����𐔂���
	float gravity_down;				//���~���̒l
	float fuel;						//�R��
	float fly;                     //�z�o�����O�̒l
	float fly_power;               //�z�o�����O�̗�
	float speed_x;
	float old_x, old_y;				//�ǂƂ��ɓ����������Ɍ��̈ʒu�ɖ߂����߂̕ϐ�
	int select_count;

	int damage_count;				//���G����
	int flashing_count;				//�_�ł̊Ԋu
	int i;                          //�X�C�b�`���ł̃��[�v�p
	int damage;                     //�G����󂯂��_���[�W�̒l
	int damage_by_second;			//�G����̎����_���l
	int damage_second;				//�����_���̎��ԃJ�E���g�p
	int damage_time;				//�����_���̃}�b�N�X����

	bool fire_flg;					//�΂̎����_�����̃t���O
	bool fire_second_bool;			//�΂̎����_����H����Ă���Ƃ��̃t���O
	bool damage_flg;				//�_���[�W���󂯂����ǂ����̃t���O
	bool move_left;					//�v���C���[�̌��� true:���@false:�E
	bool pouch_open;				//�|�[�`���J���Ă���
	bool hit_stage;					//�X�e�[�W�̃u���b�N�ɐG��Ă���

	ATTRIBUTE attribute[6];         //�e�̑���
	const char* attribute_c[6];     //�e�̑����̕�����
	int display_attribute;          //��ʂɕ\�������鑮��

	PLAYER_STATE player_state;
	
	BulletBase** bullet;             //�e�̔z��
	Stage* stage;					 //�X�e�[�W�ւ̃|�C���^
	EfectBeam* beam;
	Pouch* pouch;					 //�|�[�`�ւ̃|�C���^

	ElementItem** element;	//���f

	ChemicalFormulaParameter normal;

	ChemicalFormulaParameter* explosion;
	ChemicalFormulaParameter* poison;
	ChemicalFormulaParameter* melt;
	ChemicalFormulaParameter* pararysis;
	ChemicalFormulaParameter* heal;
public:

	Player();
	Player(Stage*);
	~Player();
	void Draw()const;
	void PouchDraw()const;
	void ChemicalFormulaDraw(int,int) const;
	void PlayerUiDraw(float,float) const;
	void Update();
	void ElementUpdate();

	void RightMove();
	void LeftMove();
	void NotInputStick();
	void Jump();
	void Hovering();
	void Fly();
	void NotFly();
	void Shoot_Gun();
	void SortBullet(int);
	void HpDamage(AttackResource);
	void Hp_Heal(int);
	bool HitBlock(const Stage*);

	BulletBase** GetBullet()const { return bullet; }
	PLAYER_STATE GetState() { return player_state; }

	//���f�̗ʂ̐ݒ�
	void SetElementItem(class Item* item);
	//�v���C���[�̌���
	bool GetMoveDirection();

	void SetExplosion(ChemicalFormulaParameter*);
	void SetPoison(ChemicalFormulaParameter*);
	void SetMelt(ChemicalFormulaParameter*);
	void SetPararysis(ChemicalFormulaParameter*);
	void SetHeal(ChemicalFormulaParameter*);

	void MoveAnimation();

#ifdef _DEBUG
	//�X�V(DotByDot)
	void Update(const PLAYER_STATE state);

	//�`��(DotByDot)
	void DebugDraw();
#endif //_DEBUG
};