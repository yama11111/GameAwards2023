#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// ビル描画用コモンクラス
class BuildingDrawerCommon
{
protected:
	// パーツの名前
	enum class Parts
	{
		Building, // ビル
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
	virtual ~BuildingDrawerCommon() = default;
};

// ビル描画用クラス
class BuildingDrawer :
	private BuildingDrawerCommon,
	private YGame::SlimeActor
{
private:
	// トランスフォーム 
	std::unique_ptr<YGame::Transform> core_;
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	// 色
	std::unique_ptr<YGame::Color> color_;
	
	// 立ちモーション用タイマー
	YMath::Timer idleTim_;
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
public:
	// 立ちモーション
	void IdleAnimation();
};

