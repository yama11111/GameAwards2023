#pragma once
#include "Sprite2D.h"
#include "SlimeActor.h"
#include "Power.h"
#include <array>

class CardDrawerCommon
{
protected:
	// 静的数字スプライト
	static std::array<std::unique_ptr<YGame::Sprite2D>, 10> sNumberSpr_;
	// 静的スプライト
	static std::unique_ptr<YGame::Sprite2D> sCardSpr_;
public:
	// 静的初期化
	static void StaticInitialize();
};

class CardDrawer : 
	private CardDrawerCommon,
	private YGame::SlimeActor
{
private:
	// 核
	std::unique_ptr<YGame::Transform> core_;
	
	// 数字用オブジェクト
	std::array<std::unique_ptr<YGame::Sprite2DObject>, 3> numObjs_;
	// ステージカードオブジェクト
	std::unique_ptr<YGame::Sprite2DObject> cardObjs_;
	// 色
	std::unique_ptr<YGame::Color> color_;

	// 数字
	int number_ = 0;

	// 選択されているか
	bool isSelected_ = false;
	// 選択されていたか
	bool isElderSelected_ = false;
	// 決定されたか
	bool isDetermined_ = false;

	// 移動用イージング
	YMath::Ease<float> moveEas_;
	// 拡大用イージング
	YMath::Ease<float> scaleEas_;
	// 選択用パワー
	YMath::Power selectPow_;
public:
	// 初期化
	void Initialize(YGame::Transform* pParent, const int number);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	// 選択設定
	void SetSelect(const bool isSelect) { isSelected_ = isSelect; }
	// 決定
	void Determine();
private:
	// 選択アニメーション更新
	void UpdateSelectAnimation();
};

