#pragma once
#include "StageDrawer.h"
#include "CardDrawer.h"
#include "LetterBoxDrawer.h"
#include "Sprite2D.h"
#include "Power.h"
#include "StageConfig.h"

class SelectDrawerCommon
{
protected:
	// 静的地球モデル
	static YGame::Model* spEarthModel_;
	// 静的ロゴスプライト
	static YGame::Sprite2D* spLogoSpr_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
	// ステージ設定ポインタ
	static StageConfig* spStageConfig_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
public:
	virtual ~SelectDrawerCommon() = default;
};

class SelectDrawer : private SelectDrawerCommon
{
private:
	// ----- オブジェクト ----- //
	
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


	// ステージカード用トランスフォーム (親)
	std::vector<std::unique_ptr<YGame::Transform>> cards_;
	// ステージカード描画クラス
	std::vector<std::unique_ptr<CardDrawer>> cardDras_;

	
	// レターボックス
	std::unique_ptr<YGame::LetterBoxDrawer> lbDra_;


	// ロゴスプライトオブジェクト
	std::unique_ptr<YGame::Sprite2DObject> logoObj_;


	// ----- アニメーション ----- //

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
	void Initalize();
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

