#pragma once
#include "IDrawer.h"
#include <array>

// ゲート描画用コモンクラス
class GateDrawerCommon
{

public:
	
	// パーツの名前
	enum class Parts
	{
		Inside, // 内枠
		InsideLight, // 内枠 (光)
		Outside, // 外枠
		OutsideLight, // 外枠 (光)
	};

protected:
	
	// パーツの総数
	static const size_t PartsNum_ = 4;

protected:
	
	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, PartsNum_> spModels_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~GateDrawerCommon() = default;
};

// ゲート描画用クラス
class GateDrawer :
	private IDrawer,
	private GateDrawerCommon
{

private:
	
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, PartsNum_> modelObjs_;

	// 色 (普通, 赤, 透明)
	std::unique_ptr<YGame::CBColor> color_;

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
	
	// 更新
	void Update();
	
	// 描画
	void Draw();

private:
	
	// 立ちモーション
	void IdleAnimation() override;

public:
	
	~GateDrawer() = default;
};

