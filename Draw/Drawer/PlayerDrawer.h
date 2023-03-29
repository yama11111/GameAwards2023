#pragma once
#include "IDrawer.h"
#include <array>

// プレイヤー描画用コモンクラス
class PlayerDrawerCommon
{
protected:
	// パーツの名前
	enum class Parts
	{
		Normal, // 通常
		Red, // 赤
	};
protected:
	// パーツの総数
	static const size_t PartsNum_ = 2;
protected:
	// モデル (パーツの数だけ)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// プレイヤー描画用クラス
class PlayerDrawer :
	private IDrawer,
	private PlayerDrawerCommon
{
private:
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// 向きポインタ
	YMath::Vector3* pDirection_ = nullptr;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親行列ポインタ (この行列に追従する)</param>
	/// <param name="pDirection"> : 向きポインタ (この向きに向く)</param>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Initialize(YMath::Matrix4* pParent, YMath::Vector3* pDirection, const Mode& mode);
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
	// 描画
	void Draw();
public:
	// ジャンプモーション
	void JumpAnimation();
	// 着地モーション
	void LandingAnimation();
	// 色替えアニメーション
	void ChangeColorAnimation(const Mode& mode);
private:
	// 立ちモーション
	void IdleAnimation() override;
};

