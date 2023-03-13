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
#define HP_BAR_WIDTH 500
#define HP_BAR_HEIGHT 50
#define FUEL_MAX 100.f
#define FUEL_BAR_HEIGHT 100

#define EXPLOSION_MAX_NUM 13	//�����̉������̌�
#define POISON_MAX_NUM 18		//�Ł@�̉������̌�
#define MELT_MAX_NUM 13			//�n���̉������̌�
#define PARARYSIS_MAX_NUM 11	//��Ⴢ̉������̌�
#define HEAL_MAX_NUM 7			//�񕜂̉������̌�

#define BULLET_MAX 50
#define GREEN GetColor(0,255,0)
#define RED GetColor(255,0,0)
#define YELLOW GetColor(255,239,0)

enum class PLAYER_STATE
{
	STOP = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	DOWN,
	DEATH
};


struct ChemicalFormulaMaterial
{
	int carbon;		//�Y�f
	int hydrogen;	//���f
	int nitrogen;	//���f
	int oxygen;		//�_�f
	int sulfur;		//����
	int chlorine;	//���f
	int uranium;	//�E����
};

struct ChemicalFormulaParameter
{
	int number_of_bullets;
	int time;
	int damage_per_second;
	int damage;
	const char* chemical_formula_name[18];
	const char* chemical_formula[10];
	ATTRIBUTE atribute;
	ChemicalFormulaMaterial material;
};

class Player : public BoxCollider
{
private:

	int image;						//�摜�p�ϐ�
	int image_size_x, image_size_y; //�摜�̃T�C�Y
	int hp;							//�̗�
	int bullet_count;				//�������e�̐�
	int shoot_count;                //�������J�E���g����
	int not_jet_count;              //����łȂ����𐔂���
	float gravity_down;				//���~���̒l
	float fuel;						//�R��
	float jump;                     //�W�����v�̒l
	float jump_power;               //�W�����v�̗�
	float speed_x;
	float old_x, old_y;				//�ǂƂ��ɓ����������Ɍ��̈ʒu�ɖ߂����߂̕ϐ�
	int select_count;
	int damage_count;				//���G����
	int flashing_count;				//�_�ł̊Ԋu
	int i;                          //�X�C�b�`���ł̃��[�v�p
	int damage;                     //�G����󂯂��_���[�W�̒l

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

	ChemicalFormulaParameter chemical_formula_explosion[13];
	ChemicalFormulaParameter chemical_formula_poison[18];
	ChemicalFormulaParameter chemical_formula_pararysis[11];
	ChemicalFormulaParameter chemical_formula_heal[7];
	ChemicalFormulaParameter chemical_formula_melt[13];
public:

	Player();
	Player(Stage*);
	~Player();
	void Draw()const;
	void Update();
	void ElementUpdate();

	void RightMove();
	void LeftMove();
	void NotInputStick();
	void Jump();
	void NotJump();
	void Shoot_Gun();
	void SortBullet(int);
	void HpDamage(AttackResource);
	void Hp_Heal(int);
	bool HitBlock(const Stage*);
	void InitChemicalParameter();
	void OpenPouch();

	BulletBase** GetBullet()const { return bullet; }
	PLAYER_STATE GetState() { return player_state; }
	ChemicalFormulaParameter GetExplosion(int);
	ChemicalFormulaParameter GetPoison(int);
	ChemicalFormulaParameter GetPararysis(int);
	ChemicalFormulaParameter GetHeal(int);
	ChemicalFormulaParameter GetMelt(int);

	//���f�̗ʂ̐ݒ�
	void SetElementItem(class Item* item);
	//�v���C���[�̌���
	bool GetMoveDirection();
};