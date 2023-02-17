#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "Bullet.h"
#include "Stage/Stage.h"
#include "EnemyBase.h"
#include "ElementItem.h"

#define JUMP_INERTIA 0.2
#define WARK_INERTIA 0.5
#define HP_MAX 100

enum class PLAYER_STATE
{
	STOP = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	DOWN,
	DEATH
};



class Player : public BoxCollider
{
private:
	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int hp;							//体力
	int bullet_count;				//撃った弾の数
	int count;                      //処理をカウントする
	int not_jet_count;              //跳んでない時を数える
	float gravity_down;				//下降時の値
	float fuel;						//燃料
	float jump;                     //ジャンプの値
	float jump_power;               //ジャンプの力
	float speed_x;
	int select_count;
	int damage_count;				//無敵時間
	int i;                          //スイッチ内でのループ用

	bool damage_flg;				//ダメージを受けたかどうかのフラグ

	Player* player;

	Attribute attribute[6];         //弾の属性
	int attribute_c[6];
	int display_attribute; //画面に表示させる属性

	PLAYER_STATE player_state;
	
	
	Bullet** bullet;             //弾の配列
	Stage* stage;                //ステージへのポインタ
	EfectBeam* beam;

	ElementItem** element;	//元素


public:
	Player();
	Player(Stage*);
	~Player();
	void Draw()const;
	void Update();
	void Element_Update();

	void RightMove();
	void LeftMove();
	void NotInputStick();
	void Jump();
	void NotJump();
	void Shoot_Gun();
	void SortBullet(int);
	void Hp_Damage(int);
	//void Being_Attacked(EnemyBase*);
	void Hp_Heal(int);

	Bullet* GetBullet(int i) { return bullet[i]; }
	PLAYER_STATE GetState() { return player_state; }

	//元素の量の設定
	void SetElementItem(class Item* item);
};