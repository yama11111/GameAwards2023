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
	static std::array<YGame::Model*, PartsNum_> spModels_;

public:
	
	// 静的初期化
	static void StaticInitialize();

public:
	
	virtual ~FilterDrawerCommon() = default;
};

// フィルター描画用クラス
class FilterDrawer :
	private IDrawer,
	private FilterDrawerCommon
{

private:
	
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// 色
	std::unique_ptr<YGame::Color> color_;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	void Initialize(YGame::Transform* pParent);
	
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

private:
	
	// 立ちモーション
	void IdleAnimation() override;

public:
	
	~FilterDrawer() = default;
};


