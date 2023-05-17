#pragma once
#include "IDrawer.h"
#include <array>

// 接合部描画用コモンクラス
class JunctionDrawerCommon
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
		eGreen, // 緑
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

	// ----- アニメーション ----- //



public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~JunctionDrawerCommon() = default;
};

// 接合部描画用クラス
class JunctionDrawer :
	private IDrawer,
	private JunctionDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// 向き
	YMath::Vector3 direction_;

	// 種類
	Type type_ = Type::eGreen;

	// 種類インデックス
	size_t typeIndex_ = 0;

	// ----- 演出 ----- //

	// 接続先
	JunctionDrawer* pPartner_ = nullptr;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="direction"> : 向き</param>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : 白</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : 黒</param>
	void Initialize(YGame::Transform* pParent, const YMath::Vector3& direction, const Type& type);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="direction"> : 向き</param>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : 白</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : 黒</param>
	void Reset(const YMath::Vector3& direction, const Type& type);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// 接続先設定
	/// </summary>
	/// <param name="pPartner"> : 接続先のポインタ</param>
	void SetPartner(JunctionDrawer* pPartner);

	/// <summary>
	/// 向き取得
	/// </summary>
	/// <returns> : 向き</returns>
	YMath::Vector3 GetDirection();

public:
	
	/// <summary>
	/// 接続
	/// </summary>
	/// <param name="pPartner"> : 接続先のポインタ</param>
	void AnimateConnection(JunctionDrawer* pPartner);

public:

	~JunctionDrawer() = default;
};

