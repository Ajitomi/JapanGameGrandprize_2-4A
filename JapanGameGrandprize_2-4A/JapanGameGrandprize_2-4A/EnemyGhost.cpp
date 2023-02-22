#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//プレイヤー発見距離
#define DETECTION_DISTANCE 500

//物理攻撃範囲
#define ATTACK_RANGE 15

//魔法攻撃範囲	
#define ATTACK_MAGIC 400

//移動スピード
#define GHOST_SPEED 1.5

//攻撃スピード
#define ATTACK_SPEED 4.5

//今日やること
//当たり判定、アイテム生成、接近攻撃あれでいいのか

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	hp = 10;
	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	standby_time = 0;
	bullet_x = 0;
	bullet_y = 0;
	player_x = 0;
	player_y = 0;
	bullet_speed_x = 0;
	bullet_speed_y = 0;
	physical_attack = false;
	magic_attack = false;
	setting = false;
	action_type = GHOST_STATE::NORMAL;
	kind = ENEMY_KIND::GHOST;
}


//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update()
{

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //通常移動
		location.x -= GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_lOWER:  //左下を目指す
		location.x -= GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_UPPER:  //左上を目指す
		location.x -= GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //右下を目指す
		location.x += GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //右上を目指す。
		location.x += GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	case GHOST_STATE::MAGIC_ATTACK: //魔法攻撃
		if (++standby_time % 300 == 0) //硬直時間
		{
			magic_attack = true;
			standby_time = 0;
		}
		break;
	case GHOST_STATE::PHYSICAL_ATTACK: //接近攻撃
		if (++standby_time % 60 == 0) //硬直時間
		{
			physical_attack = true;
			standby_time = 0;
		}
		break;
	}

	GhostAttack(); //攻撃

	if (CheckHp() == true)
	{
		
	}

}

//-----------------------------------
// 描画
//-----------------------------------
void EnemyGhost::Draw()const
{
	//スクロールに合わせて描画
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	if (action_type == GHOST_STATE::MAGIC_ATTACK) //魔法攻撃のモーション
	{
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(128, 0, 0), TRUE);
	}
	else if (action_type == GHOST_STATE::PHYSICAL_ATTACK) //接近攻撃のモーション
	{
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
	}

	if (magic_attack == true)
	{
		DrawCircle(bullet_x, bullet_y, 5, GetColor(128, 0, 0));
	}
}


//-----------------------------------
// ゴーストの動き
//-----------------------------------
void EnemyGhost::GhostMove(Player* player)
{
	int range; //プレイヤーとの距離	
	
	range = location.x - player->GetLocation().x;

	//プレイヤーが発見距離内にいたら
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (range > player->GetLocation().x) //左に移動
		{
			if (player->GetLocation().y > location.y)
			{
				action_type = GHOST_STATE::LEFT_lOWER;
			}
			else
			{
				action_type = GHOST_STATE::LEFT_UPPER;
			}
		}
		else //右に移動
		{
			if (player->GetLocation().y > location.y)
			{
				action_type = GHOST_STATE::RIGHT_LOWER;
			}
			else
			{
				action_type = GHOST_STATE::RIGHT_UPPER;
			}
		}
	}
	else //通常移動
	{
		action_type = GHOST_STATE::NORMAL;
	}

	//攻撃範囲内にいる場合
	if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE && physical_attack == false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}
	else if (range <= ATTACK_MAGIC && range >= -ATTACK_MAGIC && magic_attack == false)
	{
		player_x = player->GetLocation().x;
		player_y = player->GetLocation().y;
		action_type = GHOST_STATE::MAGIC_ATTACK;
	}

	if (HitBox(player) != false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}



}



//-----------------------------------
// ゴーストの攻撃処理
//-----------------------------------
void EnemyGhost::GhostAttack()
{

	if (magic_attack == true) //魔法攻撃
	{
		if (setting == false)
		{
			bullet_x = location.x;
			bullet_y = location.y;
			setting = true;
			// 弾の移動速度を設定する
			{
				float sb, sbx, sby, bx, by, sx, sy;

				sx = bullet_x;
				sy = bullet_y;

				bx = player_x;
				by = player_y;

				sbx = bx - sx;
				sby = by - sy;

				sb = sqrt(sbx * sbx + sby * sby);

				// １フレーム当たり2ドット移動するようにする
				bullet_speed_x = sbx / sb * 2;
				bullet_speed_y = sby / sb * 2;
			}
		}
		else
		{
			bullet_x += bullet_speed_x;
			bullet_y += bullet_speed_y;
		}

	}

	if (physical_attack == true) //物理攻撃
	{
		//どのように表現するのか未定
	}
}

//-----------------------------------
// プレイヤーの弾丸との当たり判定
//-----------------------------------
void EnemyGhost::HitBullet(BulletBase* bullet)
{

}



