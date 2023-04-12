#pragma once
#include "IDrawer.h"
#include <array>

// ブロック描画用コモンクラス
class BlockDrawerCommon
{
public:
	// パーツの名前
	enum class Parts
	{
		Cube, // 立方体
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
public:
	virtual ~BlockDrawerCommon() = default;
};

// ブロック描画用クラス
class BlockDrawer :
	private IDrawer, 
	private BlockDrawerCommon
{
private:
	// ----- オブジェクト ----- // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// 色
	std::unique_ptr<YGame::Color> color_;

	// 保存用
	Mode save_ = Mode::None;

	// ----- アニメーション	 ----- //

	// フェードイン中か
	bool isFadeIn_ = false;
	// フェードイン用タイマー
	YMath::Timer fadeInTim_;
	// フェードイン用色イージング
	YMath::Ease<YMath::Vector4> fadeInColorEas_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Initialize(YGame::Transform* pParent, const Mode& mode);
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
	// じんわり出現アニメーション
	void FadeInAnimation(const unsigned int frame);
private:
	// アニメーションリセット
	void ResetAnimation();
	// 立ちモーション
	void IdleAnimation() override;
public:
	~BlockDrawer() = default;
};

