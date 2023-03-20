#pragma once
#include "../Stage/Stage.h"
#include "../Player.h"
#include "../MapChip.h"
#include "Stage_Element_Base.h"
#include "Element_DamageWall.h"
#include "Element_Wooden_Floor.h"
#include "Element_Move_Floor.h"
#include "Element_Fall_Floor.h"
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace Element {
	//const short DEBUG_GRASS = 1;		//デバック用草ブロック
	const short DAMAGE_WALL = 40;		//ダメージ床
	const short WOODEN_FLOOR = 41;		//すり抜ける床
	const short FALL_FLOOR = 42;		//落ちる床
	const short MoveFloor = 52;			//動く床
	const short GreenButton = 61;		//緑のボタン
	const short YellowButton = 62;	//黄色のボタン
}

using namespace Element;

class Stage_Element
{
private:

	//読み込んだ画像のキャッシュマップ
	std::unordered_map<short, std::vector<int>> image_cache;

	//オブジェクト変数
	std::vector<std::shared_ptr<Stage_Element_Base>> element;
	Player* player;


	//ステージ要素のID
	std::set<short> elements_id{ /*DEBUG_GRASS,*/ DAMAGE_WALL, WOODEN_FLOOR, FALL_FLOOR,
		MoveFloor,GreenButton, YellowButton };

protected:


public:

	//コンストラクタ
	Stage_Element();

	//デストラクタ
	~Stage_Element();

	/// <summary>
	/// Stage_ElementクラスにPlayerオブジェクトを渡すSetter
	/// </summary>
	/// <param name = "*player">Playerオブジェクトポインタ</param>
	void SetPlayer(Player* player) { this->player = player; }

	/// <summary>
	/// ステージ要素の作成
	/// </summary>
	void AddElement(short type, Location location, Area area);

	/// <summary>
	/// ステージ要素の更新
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// ステージ要素の描画
	/// </summary>
	void Draw() const;

	/// <summary>
	/// マップチップ画像 Getter
	/// </summary>
	/// 既に読み込んでいる画像は同じハンドルを返す
	std::vector<int> GetImage(short type);

	/// <summary>
	/// マップチップ画像の読み込み
	/// </summary>
	std::vector<int> LoadImage(const std::string& filename);


	/// <summary>
	/// ステージ要素ID		Getter
	/// </summary>
	const std::set<short>& GetElementID() { return elements_id; }

	/// <summary>
	/// ElementオブジェクトのGetter
	/// </summary>
	/// <returns>ベクター型(Stage_Element_Baseオブジェクト型)：Stage_Element_Base</returns>	
	/// ※全要素をループして使わないこと
	std::vector<Stage_Element_Base*> GetMapChip() const {
		std::vector<Stage_Element_Base*> result;
		result.reserve(element.size());
		for (const auto& e : element) {
			result.push_back(e.get());
		}
		return result;

	};
};