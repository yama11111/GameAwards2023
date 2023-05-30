#pragma once
#include "IDrawer.h"
#include <array>

// ゴール描画用コモンクラス
class GoalDrawerCommon
{

public:
	
	// パーツの名前
	enum class Parts
	{
		Core, // 核
		InsideCore, // 内枠核
		Inside, // 内枠
		OutsideCore, // 外枠核
		Outside, // 外枠
	};

protected:
	
	// パーツの総数
	static const size_t sPartsNum_ = 5;

protected:
	
	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~GoalDrawerCommon() = default;
};

// ゴール描画用クラス
class GoalDrawer :
	private IDrawer,
	private GoalDrawerCommon
{

private:
	
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	
	// 縛る回転タイマー
	YMath::Timer bindRotaTim_;

	// 縛る回転 (内) イージング
	YMath::Ease<YMath::Vector3> inBindRotaEas_;
	
	// 縛る回転 (外) イージング
	YMath::Ease<YMath::Vector3> outBindRotaEas_;


	// クリア演出
	bool isClear_ = false;
	
	// ロックフラグ
	bool isRock_ = false;


	// ログインフラグ
	bool isActLogin_ = false;

	// ログインタイマー
	YMath::Timer loginTim_;


	// ハッキング回転フラグ
	bool isActHackRota_ = false;

	// ハッキング回転タイマー
	YMath::Timer hackRotaTim_;

	// ハッキング回転 (内) スピード
	YMath::Vector3 inHackRotaSpeed_;
	
	// ハッキング回転 (外) スピード
	YMath::Vector3 outHackRotaSpeed_;


	// クリア回転フラグ
	bool isActClearRota_ = false;

	// クリア回転タイマー
	YMath::Timer clearRotaTim_;

	// クリア回転 (内) イージング
	YMath::Ease<YMath::Vector3> inClearRotaEas_;

	// クリア回転 (外) イージング
	YMath::Ease<YMath::Vector3> outClearRotaEas_;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="isRock"> : ロックするか</param>
	void Initialize(YGame::Transform* pParent, const bool isRock);
	
	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="isRock"> : ロックするか</param>
	void Reset(const bool isRock);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:

	///
	void Unlock();

	/// <summary>
	/// クリア演出
	/// </summary>
	/// <param name="playerPos"> : プレイヤーの位置</param>
	void ActivateClearAnimation(const YMath::Vector3& playerPos);

private:

	// ログイン開始
	void StartLogin(const YMath::Vector3& emitStartPos);
	
	// ハッキング回転開始
	void StartHackRota();

	// クリア回転開始
	void StartClearRota();
	
	// 縛る回転アニメーション
	void BindRotaAnimation();

	// クリア回転アニメーション
	void ClearAnimation();

};

