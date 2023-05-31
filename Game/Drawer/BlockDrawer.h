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
		eCore, // 核
		eShell, // 殻
		eEnd, // リサイズ用
	};

	// 種類
	enum class Type
	{
		eBlack, // 白
		eWhite, // 黒
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// 種類の総数
	static const size_t sTypeNum_ = static_cast<size_t>(Type::eEnd);

protected:

	// ----- ブロック ----- //

	// モデル (パーツの数だけ)
	static std::array<std::array<YGame::Model*, sPartsNum_>, sTypeNum_> spModels_;


public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~BlockDrawerCommon() = default;
};

// ブロック描画用クラス
class BlockDrawer :
	private IDrawer,
	private BlockDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// 種類
	Type type_ = Type::eBlack;

	// 種類インデックス
	size_t typeIndex_ = 0;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : 白</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : 黒</param>
	void Initialize(YGame::Transform* pParent, const Type& type);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : 白</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : 黒</param>
	void Reset(const Type& type);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:

	~BlockDrawer() = default;
};

