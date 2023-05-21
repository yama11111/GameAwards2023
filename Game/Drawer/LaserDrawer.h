#pragma once
#include "IDrawer.h"
#include <array>

// レーザー描画用コモンクラス
class LaserDrawerCommon
{

public:

	// パーツの名前
	enum class Parts
	{
		eBase, // 台座
		eCore, // 核
		eFunnel1, // ファンネル1
		eFunnel2, // ファンネル2
		eFunnel3, // ファンネル3
		eFunnel4, // ファンネル4
		eBeam, // ビーム
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

protected:

	// ----- レーザー ----- //

	// 射出モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	
	// ----- 演出 ----- //

	// ビーム立ち回転イージング
	static YMath::Ease<float> sIdleBeamRotaEase_;

	// ファンネル立ち回転イージング
	static YMath::Ease<float> sIdleFannelRotaEase_;


	// ファンネル発射高度イージング
	static YMath::Ease<float> sShootFannelHeightEase_;

	// ファンネル発射位置係数イージング
	static YMath::Ease<float> sShootFannelPosFactorEase_;

	// ファンネル発射回転イージング
	static YMath::Ease<float> sShootFannelRotaEase_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~LaserDrawerCommon() = default;
};

// レーザー描画用クラス
class LaserDrawer :
	private IDrawer,
	private LaserDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// 長さポインタ
	float* pLength_ = nullptr;


	// ----- 演出 ----- //

	// 動いているか
	bool isAct_ = false;

	// ファンネル位置 (アニメ用)
	std::array<YMath::Vector3, 4> animeFunnelPoss_;

	// ビーム回転 (アニメ用)
	YMath::Vector3 animeFunnelRota_;

	// ビーム位置 (アニメ用)
	YMath::Vector3 animeBeamPos_;

	// ビーム回転 (アニメ用)
	YMath::Vector3 animeBeamRota_;

	// ビーム大きさ (アニメ用)
	YMath::Vector3 animeBeamSca_;


	// 立ちモーション中か
	bool isIdle_ = false;

	// 立ちモーション用タイマー
	YMath::Timer idleTimer_;


	// 発射したか
	bool isShooted_ = false;

	// 発射イージング用タイマー
	YMath::Timer shootTimer_;

	// ビーム発射大きさイージング
	YMath::Ease<YMath::Vector3> shootBeamScaEase_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="pLength"> : 長さポインタ</param>
	void Initialize(YGame::Transform* pParent, float* pLength);

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
	/// 発射アニメーション
	/// </summary>
	void AnimateShoot();

private:

	/// <summary>
	/// 立ちモーション更新
	/// </summary>
	void UpdateIdleAnimation();

	/// <summary>
	/// 発射アニメーション更新
	/// </summary>
	void UpdateShootAnimation();

public:

	~LaserDrawer() = default;
};

