#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class SLIME_ATTACK
{
	BEFORE_ATTACK,//攻撃する前
	AFTER_ATTACK,//攻撃した後
};

class EnemySlime :
	public EnemyBase
{
private:
	bool attack; //攻撃が当たったか

	int color;
	SLIME_ATTACK slime_attack;

	int slime_image;
	int slime_angle;
	int wait_time;

	Location jump_distance;

	ElementItem drop_item;
public:

	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//描画以外の更新を実行
	virtual void Update(const class Player* player, const class Stage* stage)override;
	//描画
	virtual void Draw()const override;

	//アイドル状態
	void Idol() override;

	//移動
	void Move(const Location player_location) override;

	//落下
	void Fall() override;

	//攻撃
	void  Attack(Location) override;

	//攻撃が当たっているか
	AttackResource Hit() override;

	//死亡
	void Death() override;

	virtual void HitBullet(const BulletBase* bullet)override;

	//座標の取得
	Location GetLocation() const override;
};