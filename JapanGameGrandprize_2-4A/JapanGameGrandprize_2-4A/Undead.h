#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Player.h"

class Undead :
    public EnemyBase
{
private:

    bool attack; //攻撃が当たったか
    int damage; //ダメージ
    int attack_interval; //次の攻撃までの時間
    int animation; //アニメーション
    int image_argument; //画像の引数
    int attack_time; //攻撃している時間(デバッグ用)
private:
    //プレイヤーとの距離
    void DistancePlayer(const Location player_location);

    //移動時のアニメーション
    void MoveAnimation();
public:

    //コンストラクタ
    Undead();

    //デストラクタ
    ~Undead();

    //描画以外の更新
    void Update(const class Player* player, const class Stage* stage) override;

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

    //プレイヤーの弾との当たり判定
    void HitBullet(const BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //座標の取得
    Location GetLocation() const override;
};