#pragma once
#include "IDrawer.h"
#include <array>

// 足場描画用コモンクラス
class PlatformDrawerCommon
{

public:

	// パーツの名前
	enum class Parts
	{
		eHologram, // ホログラム
		eLeft, // 左
		eRight, // 右
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// ホログラム用マテリアル
	static std::unique_ptr<YGame::CBMaterial> sHologramMate_;

protected:

	// ----- 足場 ----- //

	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~PlatformDrawerCommon() = default;
};

// 足場描画用クラス
class PlatformDrawer :
	private IDrawer,
	private PlatformDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

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

	~PlatformDrawer() = default;
};
