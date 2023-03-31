#pragma once
#include "IDrawer.h"
#include <array>

// ゴール描画用コモンクラス
class GoalDrawerCommon
{
public:
	// パーツの名前
	enum class Parts
	{
		Core, // 核
		Inside, // 内枠
		Outside, // 外枠
		Base, // 台座
	};
protected:
	// パーツの総数
	static const size_t PartsNum_ = 4;
protected:
	// モデル (パーツの数だけ)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// ゴール描画用クラス
class GoalDrawer :
	private IDrawer,
	private GoalDrawerCommon
{
private:
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	void Initialize(YGame::Transform* pParent);
	// リセット (中身だけ初期化)
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
private:
	// 立ちモーション
	void IdleAnimation() override;
};

