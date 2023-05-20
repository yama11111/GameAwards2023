#pragma once
#include "IDrawer.h"
#include <array>

// ばね描画用コモンクラス
class SpringDrawerCommon
{

public:

	// パーツの名前
	enum class Parts
	{
		eBase, // 台座
		eCore, // 核
		eTopCore, // 上核
		eTopShell, // 上殻
		eBottomCore, // 下核
		eBottomShell, // 下殻
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);
	
	// 輪っかの数
	static const size_t sRingNum_ = 2;

protected:

	// ----- ブロック ----- //

	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	// ----- アニメーション ----- //

	// 立ち高さイージング
	static std::array<YMath::Ease<float>, sRingNum_> sIdleHeightEases_;
	
	// 立ち回転スピードイージング
	static YMath::Ease<float> sIdleRotaSpeedEase_;


	// ジャンプ予備動作高さイージング
	static YMath::Ease<float> sJumpAnticipationHeightEase_;
	
	// ジャンプ高さイージング
	static std::array<YMath::Ease<float>, sRingNum_> sJumpHeightEases_;

	// ジャンプ予備動作大きさイージング
	static YMath::Ease<YMath::Vector3> sJumpAnticipationScaleEase_;

	// ジャンプ大きさイージング
	static std::array<YMath::Ease<YMath::Vector3>, sRingNum_> sJumpScaleEases_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~SpringDrawerCommon() = default;
};

// ばね描画用クラス
class SpringDrawer :
	private IDrawer,
	private SpringDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// ----- 演出 ----- //

	// 動いているか
	bool isAct_ = false;


	// 位置 (アニメ用)
	std::array<YMath::Vector3, sRingNum_> animePoss_;

	// 回転 (アニメ用)
	std::array<YMath::Vector3, sRingNum_> animeRotas_;

	// 大きさ (アニメ用)
	std::array<YMath::Vector3, sRingNum_> animeScales_;


	// 立ちモーションか
	bool isIdle_ = false;

	// 立ちタイマー
	YMath::Timer idleTimer_;


	// 立ち高さモーションか
	bool isIdleHeight_ = false;
	
	// 立ち高さ下リングをモーション開始するか
	bool isIdleHeightBottomStart_ = false;
	
	// 立ちパワー
	std::array<YMath::Power, sRingNum_> idlePowers_;

	// 立ちパワースイッチ
	std::array<bool, sRingNum_> isIdlePowerSwitches_;


	// ジャンプしたか
	bool isJumped_ = false;
	
	// ジャンプ予備動作パワー
	YMath::Power jumpAnticipationPower_;

	// ジャンプ予備動作パワースイッチ
	bool isJumpedAnticipationSwitch_ = false;
	
	// ジャンプパワー
	std::array<YMath::Power, sRingNum_> jumpPowers_;
	
	// ジャンプパワースイッチ
	bool isJumpedSwitch_ = false;

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

	/// <summary>
	/// ジャンプ
	/// </summary>
	void AnimateJump();

private:

	/// <summary>
	/// 立ちモーション更新
	/// </summary>
	void UpdateIdle();

	/// <summary>
	/// ジャンプアニメーション更新
	/// </summary>
	void UpdateJump();

public:

	~SpringDrawer() = default;
};

