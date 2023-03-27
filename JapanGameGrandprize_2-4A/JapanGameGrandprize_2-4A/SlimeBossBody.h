//#pragma once
//#include"EnemyBase.h"
//#include"CameraWork.h"
//
//enum class BODY_TYPE
//{
//	head,
//	body
//};
//
//class SlimeBossBody:
//	public EnemyBase
//{
//private:
//
//	bool attack; //攻撃が当たったか
//
//	int slimeboss_image;
//	BODY_TYPE body_type;
//public:
//
//	SlimeBossBody(int x, int y, int speed, int hp, int slime_min_drop, int slime_drop, BODY_TYPE body_type);
//	~SlimeBossBody();
//
//	//描画以外の更新を実行
//	virtual void Update(const class Player* player, const class Stage* stage)override;
//	//描画
//	virtual void Draw()const override;
//
//	//移動
//	void Move(const Location player_location) override;
//
//	//落下
//	void Fall() override;
//	
//	void Idol() override;
//
//	//攻撃
//	void  Attack(Location) override;
//
//	//攻撃が当たっているか
//	AttackResource Hit() override;
//
//	//死亡
//	void Death() override;
//
//	virtual void HitBullet(const BulletBase* bullet)override;
//
//	//座標の取得
//	Location GetLocation() const override;
//
//	void SetLocation(Location location);
//
//	BODY_TYPE GetBodyType() const { return body_type; }
//};