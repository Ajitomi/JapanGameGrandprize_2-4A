#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"


struct ATTACK_START
{
	float x;	//縦
	float y;	//横
};

enum DIRECTION
{
	left = -1,
	right = 1
};

enum class SLIME_STATE
{
	IDOL,   //アイドル状態
	MOVE,   //移動
	ATTACK, //攻撃
	DEATH,  //死亡
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	int a;
	int direction;
	int jump_angle;

	ATTACK_START attack_start;
	SLIME_STATE state;

public:
	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//描画以外の更新を実行
	virtual void Update()override;
	//描画
	virtual void Draw()const override;

	void Hit();
	void HitStage();
	void AttackJudgement(BoxCollider* boxcollider);
	void Attack();
};
