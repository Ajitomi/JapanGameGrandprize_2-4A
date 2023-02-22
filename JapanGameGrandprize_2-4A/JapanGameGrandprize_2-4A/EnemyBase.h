#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "EnumEnemyType.h"

//各属性のドロップ数
#define FIRE_DROP 3
#define WATER_DROP 4
#define WIND_DROP 3
#define SOIL_DROP 4
#define THUNDER_DROP 7

//エネミーの種類
enum class ENEMY_KIND
{
	/*雑魚敵*/
	SLIME = 0,	//スライム
	UNDEAD,		//アンデット
	HARPY,		//ハーピィ
	MAGE,		//メイジ
	GHOST,		//ゴースト
	WYVERN,		//ワイバーン

	/*ボス*/
	KING_SLIME, //スライムキング
	TORRENT,	//トレント
	GARGOYLE,	//ガーゴイル
	DRAGON,		//ドラゴン
	END_BOSS,	//ラスボス
	NONE
};



class EnemyBase
{
public:
	//コンストラクタ
	EnemyBase();

	//デストラクタ
	~EnemyBase() {}

	//描画以外の更新を実行
	virtual void Update() = 0;

	//描画
	virtual void Draw() const = 0;

	//プレイヤーの弾との当たり判定
	virtual void HitBullet(BulletBase* bullet) = 0;

	//ドロップする種類の量の取得
	int GetDropTypeVolume() const;

	//ドロップするアイテムの量の取得
	int GetDropVolume()const;

	//ドロップアイテムの取得
	ElementItem GetDropItem(int i) const;

	//エネミーの種類の取得
	ENEMY_KIND GetEnemyKind() const;

	//削除可能状態の取得
	bool GetCanDelete() const;

protected:
	bool can_delete; //削除フラグ
	int hp;	//体力
	int speed; //移動速度

	int drop_volume; //ドロップ量
	int drop_type_volume; //ドロップする種類の量

	ElementItem** drop_element; //ドロップ元素

	ENEMY_KIND kind; //エネミーの種類
	ENEMY_TYPE* type; //エネミーのタイプ
protected:
	//HPが0かどうか判断(0になったらtrue)
	bool CheckHp();
};