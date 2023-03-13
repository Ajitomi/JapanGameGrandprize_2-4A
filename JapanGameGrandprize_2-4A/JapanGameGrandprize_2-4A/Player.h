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
	const char* material_name[10];
	ATTRIBUTE atribute;
	ChemicalFormulaMaterial material;
};

struct ChemicalFormulaExplosion
{
	ChemicalFormulaParameter nitroglycerin;
	ChemicalFormulaParameter tnt;
	ChemicalFormulaParameter diazodinitrophenol;
	ChemicalFormulaParameter picric_acid;
	ChemicalFormulaParameter pen_slit;
	ChemicalFormulaParameter Hexogen;
	ChemicalFormulaParameter hmx;
	ChemicalFormulaParameter acetone_peroxide;
	ChemicalFormulaParameter nitro_glycol;
	ChemicalFormulaParameter hniw;
	ChemicalFormulaParameter trimethylene_nitramine;
	ChemicalFormulaParameter nitroguanidine;
	ChemicalFormulaParameter fox_7;
};

struct ChemicalFormulaPoison
{
	ChemicalFormulaParameter dinitrogen_tetroxide;
	ChemicalFormulaParameter mustard_gas;
	ChemicalFormulaParameter aniline;
	ChemicalFormulaParameter histamine;
	ChemicalFormulaParameter cs_gus;
	ChemicalFormulaParameter naphthol;
	ChemicalFormulaParameter ciguatoxin;
	ChemicalFormulaParameter tetrodotoxin;
	ChemicalFormulaParameter toxiferin;
	ChemicalFormulaParameter strychnine;
	ChemicalFormulaParameter chrysanthemum_acid;
	ChemicalFormulaParameter Rotenone;
	ChemicalFormulaParameter saxitoxin;
	ChemicalFormulaParameter lysine;
	ChemicalFormulaParameter solanine;
	ChemicalFormulaParameter anisatin;
	ChemicalFormulaParameter hyoscyamine;
	ChemicalFormulaParameter palytoxin;
};

struct ChemicalFormulaPararysis
{
	ChemicalFormulaParameter ether;
	ChemicalFormulaParameter allylamine;
	ChemicalFormulaParameter indole;
	ChemicalFormulaParameter skatole;
	ChemicalFormulaParameter heptanoic_acid;
	ChemicalFormulaParameter thalidomaide;
	ChemicalFormulaParameter nicotine;
	ChemicalFormulaParameter lycorine;
	ChemicalFormulaParameter lobeline;
	ChemicalFormulaParameter batrachotoxin;
	ChemicalFormulaParameter aconitine;
};

struct ChemicalFormulaHeal
{
	ChemicalFormulaParameter aspartic_acid;
	ChemicalFormulaParameter ibotenic_acid;
	ChemicalFormulaParameter glutamic_acid;
	ChemicalFormulaParameter tricolominic_acid;
	ChemicalFormulaParameter glutamine;
	ChemicalFormulaParameter glucose;
	ChemicalFormulaParameter sugar;
};

struct ChemicalFormulaMelt
{
	ChemicalFormulaParameter hydrochloric_acid;
	ChemicalFormulaParameter aqua_regia;
	ChemicalFormulaParameter suluric_acid;
	ChemicalFormulaParameter acetic_acid;
	ChemicalFormulaParameter nitric_acid;
	ChemicalFormulaParameter formic_acid;
	ChemicalFormulaParameter methanesulfonic_acid;
	ChemicalFormulaParameter benzenesulfonic_acid;
	ChemicalFormulaParameter p_toluenesulfonic_acid;
	ChemicalFormulaParameter chloric_acid;
	ChemicalFormulaParameter perchloric_acid;
	ChemicalFormulaParameter thiosulfate;
	ChemicalFormulaParameter hydrogen_sulfide;
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
	void OpenPouch();

	BulletBase** GetBullet()const { return bullet; }
	PLAYER_STATE GetState() { return player_state; }

	//���f�̗ʂ̐ݒ�
	void SetElementItem(class Item* item);
	//�v���C���[�̌���
	bool GetMoveDirection();
};