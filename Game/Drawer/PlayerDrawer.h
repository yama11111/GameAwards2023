#pragma once
#include "IDrawer.h"
#include <array>

// プレイヤー描画用コモンクラス
class PlayerDrawerCommon
{

public:
	
	// パーツの名前
	enum class Parts
	{
		eBody, // 体
		eEnd, // リサイズ用
	};

protected:
	
	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

protected:
	
	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	static YGame::Audio* spJumpSE_;
	
	static YGame::Audio* spDeadSE_;


public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~PlayerDrawerCommon() = default;
};

// プレイヤー描画用クラス
class PlayerDrawer :
	private IDrawer,
	private PlayerDrawerCommon
{

private:
	
	// ----- オブジェクト ----- //
	
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;
	
	// 色
	std::unique_ptr<YGame::CBColor> color_;

	// 向きポインタ
	YMath::Vector3* pDirection_ = nullptr;

	
	// モデル用オブジェクト (テレポート)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> teleportModelObjs_;

	// 色
	std::unique_ptr<YGame::CBColor> teleportColor_;
	

	// ----- アニメーション ----- //

	// アニメーション用
	YMath::Vector3 animePos{}, animeRota{}, animeScale{};
	
	YMath::Vector3 teleportAnimePos{}, teleportAnimeRota{}, teleportAnimeScale{};

	// 移動中か
	bool isMove_ = false;
	
	// 移動していたか
	bool isElderMove_ = false;

	// 移動用回転パワー
	YMath::Power moveRotaPow_;

	// 移動用回転イージング
	YMath::Ease<float> moveRotaEas_;

	// 移動用エミットタイマー
	YMath::Timer moveEmitTimer_;


	// テレポート中か
	bool isTeleport_ = false;

	// テレポートタイマー
	YMath::Timer teleportTim_;

	// テレポート用アルファ値イージング
	YMath::Ease<float> teleportAlphaEas_;

	// テレポート用スケールイージング
	YMath::Ease<float> teleportScaleEas_;


	// 死亡中か
	bool isDead_ = false;

	// 死亡タイマー
	YMath::Timer deadTim_;


	// リスポーン中か
	bool isRespawn_ = false;
	
	// リスポーン用タイマー
	YMath::Timer respawnTim_;
	
	// リスポーン用スケールイージング
	YMath::Ease<float> respScaleEas_;
	
	// リスポーン用アルファ値イージング
	YMath::Ease<float> respAlphaEas_;


	// ゴールしたか
	bool isGoal_ = false;

	// ゴール用タイマー
	YMath::Timer goalTim_;

	// ゴール用スケールイージング
	YMath::Ease<float> goalScaleEas_;

	// ゴール用アルファ値イージング
	YMath::Ease<float> goalAlphaEas_;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="pDirection"> : 向きポインタ (この向きに向く)</param>
	void Initialize(YGame::Transform* pParent, YMath::Vector3* pDirection);
	
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

	bool IsEndDeadAnime() const { return deadTim_.IsEnd(); }

public:
	
	// 移動モーション
	void SetActMoveAnimation(const bool isMove) { isMove_ = isMove; }
	
	// ジャンプモーション
	void AnimateJump();
	
	// 着地モーション
	void AnimateLanding();


	// テレポートモーション
	void AnimateTeleport();


	// 死亡アニメーション
	void AnimateDead();
	
	// リスポーンアニメーション
	void AnimateRespawn();

	// ゴールアニメーション
	void AnimateGoal();

private:
	
	// アニメーションリセット
	void ResetAnimation();

	// 移動アニメーション
	void UpdateMoveAnimation();
	
	// テレポートアニメーション
	void UpdateTeleportAnimation();
	
	// 死亡アニメーション
	void UpdateDeadAnimation();

	// リスポーンアニメーション
	void UpdateRespawnAnimation();

	// ゴールアニメーション
	void UpdateGoalAnimation();

	// 煙発生更新
	void UpdateSmokeEmitter();

public:
	
	~PlayerDrawer() = default;
};

