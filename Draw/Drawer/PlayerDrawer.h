#pragma once
#include "IDrawer.h"
#include <array>

// プレイヤー描画用コモンクラス
class PlayerDrawerCommon
{
public:
	// パーツの名前
	enum class Parts
	{
		Body, // 体
	};
protected:
	// パーツの総数
	static const size_t PartsNum_ = 2;
protected:
	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, PartsNum_> spModels_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
public:
	virtual ~PlayerDrawerCommon() = default;
};

// プレイヤー描画用クラス
class PlayerDrawer :
	private IDrawer,
	private PlayerDrawerCommon
{
private:
	// ----- オブジェクト ----- //
	
	// モデル用オブジェクト (子)
	std::array<std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_>, ModeNum_> modelObjs_;

	// 色 (普通, 赤, 透明)
	std::array<std::unique_ptr<YGame::Color>, ModeNum_> colors_;

	// 向きポインタ
	YMath::Vector3* pDirection_ = nullptr;

	// ----- アニメーション ----- //

	// リスポーン中か
	bool isRespawn_ = false;
	// リスポーン用タイマー
	YMath::Timer respawnTim_;
	// リスポーン用スケールイージング
	YMath::Ease<float> respScaleEas_;
	// リスポーン用アルファ値イージング
	YMath::Ease<float> respAlphaEas_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="pDirection"> : 向きポインタ (この向きに向く)</param>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Initialize(YGame::Transform* pParent, YMath::Vector3* pDirection, const Mode& mode);
	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Reset(const Mode& mode);
	// 更新
	void Update();
	// 前方描画 (フィルターより 先 に呼ぶ)
	void PreDraw();
	// 後方描画 (フィルターより 後 に呼ぶ)
	void PostDraw();
public:
	// ジャンプモーション
	void JumpAnimation();
	// 着地モーション
	void LandingAnimation();
	// 色替えアニメーション
	void ChangeColorAnimation(const Mode& mode);
	// リスポーンアニメーション
	void RespawnAnimation();
private:
	// アニメーションリセット
	void ResetAnimation();
	// 立ちモーション
	void IdleAnimation() override;
public:
	~PlayerDrawer() = default;
};

