#pragma once
#include "IDrawer.h"
#include <array>

// フィルター描画用コモンクラス
class FilterDrawerCommon
{
public:
	// パーツの名前
	enum class Parts
	{
		Monitor, // モニター
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

// フィルター描画用クラス
class FilterDrawer :
	private IDrawer,
	private FilterDrawerCommon
{
private:
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親行列ポインタ (この行列に追従する)</param>
	void Initialize(YMath::Matrix4* pParent);
	// リセット (中身だけ初期化)
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
private:
	// 立ちモーション
	void IdleAnimation() override;
public:
	~FilterDrawer() = default;
};


