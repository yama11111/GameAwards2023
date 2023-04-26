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
public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

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
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	
	// 色
	std::unique_ptr<YGame::Color> color_;

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
	void Initialize(YGame::Transform* pParent, YMath::Vector3* pDirection);
	
	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	void Reset();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	
	// ジャンプモーション
	void JumpAnimation();
	
	// 着地モーション
	void LandingAnimation();
	
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

