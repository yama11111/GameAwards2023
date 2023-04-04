#pragma once
#include "StageDrawer.h"
#include "Sprite2D.h"
#include "Power.h"

class SelectDrawerCommon
{
protected:
	// 静的数字スプライト
	static std::array<std::unique_ptr<YGame::Sprite2D>, 10> sNumberSpr_;
	// 静的スプライト
	// static std::unique_ptr<YGame::Sprite2D> sStageSpr_;
	// 静的地球モデル
	static std::unique_ptr<YGame::Model> sEarthModel_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

class SelectDrawer : private SelectDrawerCommon
{
private:
	// 核
	std::unique_ptr<YGame::Transform> core_;
	
	
	// 地球モデルオブジェクト
	std::unique_ptr<YGame::ModelObject> earthObj_;
	// 色
	std::unique_ptr<YGame::Color> color_;

	
	// ステージトランスフォーム (使う用)
	std::array<std::unique_ptr<YGame::Transform>, 24> aliveStages_;
	// ステージトランスフォーム (使わない用)
	std::unique_ptr<YGame::Transform> deadStage_;
	// ステージ描画クラス
	std::vector<std::unique_ptr<StageDrawer>> stageDras_;

	
	// ステージ番号ポインタ
	int* pStageIdx_ = nullptr;

	// 動作中か
	bool isAct_ = false;
	
	// 開始時回転用イージング
	YMath::Ease<float> startRotaEas_;
	// 開始時回転用タイマー
	YMath::Timer startRotaTim_;
	
	// ステージ回転用イージング
	YMath::Ease<float> stageRotaEas_;
	// ステージ回転用パワー
	std::vector<YMath::Power> stageRotaPows_;
public:
	// 初期化
	void Initalize(int* pStageIdx);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画 (モデル)
	void DrawModel();
	// 描画 (スプライト2D)
	void DrawSprite3D();
	// 描画 (スプライト3D)
	void DrawSprite2D();
public:
	// 動作設定
	void SetActive(const bool isAct) { isAct_ = isAct; }
private:
	// アニメーションの回転更新
	void UpdateRotaAnimation();
};

