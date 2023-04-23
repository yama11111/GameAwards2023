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
		Core, // 核
		Shell, // 殻
	};

protected:

	// パーツの総数
	static const size_t PartsNum_ = 2;

	// 状態の数
	static const size_t ModeNum_ = 2;

protected:

	// ----- ブロック ----- //

	// モデル (パーツの数だけ)
	static std::array<std::array<YGame::Model*, PartsNum_>, ModeNum_> spModels_;

	// 核色
	static std::array<std::unique_ptr<YGame::Color>, ModeNum_> sCoreColor_;

	// 核マテリアル
	static std::unique_ptr<YGame::Material> sCoreMate_;


	// 核色用パワー
	static YMath::Power coreColorPow_;

	// 核色パワースイッチ
	static bool isSwitchCoreColorPower_;

	// 核色イージング
	static std::array<YMath::Ease<YMath::Vector4>, ModeNum_> coreColorEas_;


	// ----- グリッド ----- //

	// グリッドモデル
	static YGame::Model* spGridModel_;

	// グリッド色
	static std::unique_ptr<YGame::Color> sGridColor_;

	// グリッドマテリアル
	static std::unique_ptr<YGame::Material> sGridMate_;


	// 取得時大きさイージング
	static YMath::Ease<float> catchGridScaleValueEas_;

	// 取得失敗時大きさイージング
	static YMath::Ease<float> failToCatchGridScaleValueEas_;

	// 設置時大きさイージング
	static YMath::Ease<float> placeGridScaleValueEas_;

	// 設置失敗時大きさイージング
	static YMath::Ease<float> failToPlaceGridScaleValueEas_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的リセット
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();

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
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// グリッドモデル用オブジェクト
	std::unique_ptr<YGame::ModelObject> gridObj_;

	// ----- アニメーション ----- //

	// 失敗用シェイク
	YMath::Shake failureShake_;


	// グリッド動作フラグ
	bool isActGrid_ = false;


	// 取得可能状態か
	bool isCanCatch_ = false;

	// 前は取得可能状態だったか
	bool isElderCanCatch_ = false;


	// 取得アニメーションをするか
	bool isActCatchAnimition_ = false;

	// 取得時イージング用タイマー
	YMath::Timer catchGridTim_;

	// 取得失敗アニメーションをするか
	bool isActFailToCatchAnimition_ = false;

	// 取得失敗時イージング用タイマー
	YMath::Timer failToCatchGridTim_;


	// 置ける状態か
	bool isCanPlace_ = false;

	// 前は置ける状態だったか
	bool isElderCanPlace_ = false;


	// 設置アニメーションをするか
	bool isActPlaceAnimition_ = false;

	// 設置時イージング用タイマー
	YMath::Timer placeGridTim_;

	// 設置失敗アニメーションをするか
	bool isActFailToPlaceAnimition_ = false;

	// 設置失敗時イージング用タイマー
	YMath::Timer failToPlaceGridTim_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	void Initialize(YGame::Transform* pParent, const Mode& mode);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	void Reset(const Mode& mode);

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
	/// フィルターで取得可能か設定
	/// </summary>
	/// <param name="isCanCatch"> : 取得可能状態か</param>
	void SetIsCanCatch(const bool isCanCatch) { isCanCatch_ = isCanCatch; }

	/// <summary>
	/// 取得アニメーション
	/// </summary>
	void CatchAnimation();

	/// <summary>
	/// 取得できないアニメーション
	/// </summary>
	void FailToCatchAnimation();


	/// <summary>
	/// 置けるか設定
	/// </summary>
	/// <param name="isCanPlace"> : 置けるか</param>
	void SetIsCanPlace(const bool isCanPlace) { isCanPlace_ = isCanPlace; }

	/// <summary>
	/// 設置アニメーション
	/// </summary>
	void PlaceAnimation();

	/// <summary>
	/// 設置できないアニメーション
	/// </summary>
	void FailToPlaceAnimation();

private:

	/// <summary>
	/// 取得可能アニメーション
	/// </summary>
	void CanCatchAnimation();

	/// <summary>
	/// 置けない状態アニメーション
	/// </summary>
	void NotPlaceAnimation();

	/// <summary>
	/// 立ちモーション
	/// </summary>
	void IdleAnimation() override;

public:

	~BlockDrawer() = default;
};

