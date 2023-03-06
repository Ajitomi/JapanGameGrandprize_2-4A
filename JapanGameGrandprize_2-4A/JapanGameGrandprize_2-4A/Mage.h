#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "EnemyBulletBase.h"

#define MAGE_BULLET_MAX 5

class Mage :
    public EnemyBase
{
private:
    bool can_teleport; //テレポート可能か

    int shot_rate; //魔法弾の発射レート
    int shot_count; //発射した弾の数
    int image; //画像
    int drop; //ドロップするアイテムの種類の数
    int attack_interval; //攻撃の間隔

private:
    //テレポート
    void Teleport();

    //弾の生成
    void CreateBullet(Location);

public:

    //コンストラクタ
    Mage();

    //デストラクタ
    ~Mage();

    //更新
    void Update() override;

    //アイドル状態
    void Idol() override;

    //移動
    void Move(const Location player_location) override;

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

