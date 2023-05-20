#pragma once
#include "IDrawer.h"
#include <array>

// 鍵描画用コモンクラス
class KeyDrawerCommon
{

public:

	// パーツの名前
	enum class Parts
	{
		eBlade, // 刃
		eRingCore, // リング核
		eRingShell, // リング殻
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// パーツセットの数
	static const size_t sSetNum_ = 2;

protected:

	// ----- 鍵 ----- //

	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	// ----- アニメーション ----- //
	
	// 立ち高さイージング
	static YMath::Ease<float> sIdleHeightEase_;


public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~KeyDrawerCommon() = default;
};

// 鍵描画用クラス
class KeyDrawer :
	private IDrawer,
	private KeyDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;


	// ----- 演出 ----- //

	// 動いているか
	bool isAct_ = false;


	// 刃位置 (アニメ用)
	YMath::Vector3 animeBladePos_;
	

	// リング位置 (アニメ用)
	YMath::Vector3 animeRingPos_;

	// リング回転 (アニメ用)
	YMath::Vector3 animeRingRota_;
	

	// 立ちモーションか
	bool isIdle_ = false;

	// 立ち高さパワー
	std::array<YMath::Power, sSetNum_> idlePowers_;

	// 立ち高さパワースイッチ
	std::array<bool, sSetNum_> isIdlePowerSwitches_;


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

	/// <summary>
	/// 立ちモーション更新
	/// </summary>
	void UpdateIdleAnimation();

public:

	~KeyDrawer() = default;
};
