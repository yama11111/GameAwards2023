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
		Cube, // 立方体
	};

protected:
	
	// パーツの総数
	static const size_t PartsNum_ = 2;

protected:
	
	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, PartsNum_> spModels_;
	
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	static void StaticInitialize(YGame::ViewProjection* pVP);

public:
	
	virtual ~BlockDrawerCommon() = default;
};

// ブロック描画用クラス
class BlockDrawer :
	private IDrawer, 
	private BlockDrawerCommon
{

private:

	// ----- オブジェクト ----- // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// 色
	std::unique_ptr<YGame::Color> color_;

	// ----- アニメーション	 ----- //

	// 取得可能状態か
	bool isRetrievable_ = false;

	// 前は取得可能状態だったか
	bool isElderRetrievable_ = false;

	// 取得可能アニメーション用タイマー
	YMath::Timer RetrievableTim_;


	// 置ける状態か
	bool isCanPlace_ = false;

	// 前は置ける状態だったか
	bool isElderCanPlace_ = false;


	// 置けなかった時用シェイク
	YMath::Shake notPlaceShake_;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::Invisible"> : 透明状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Initialize(YGame::Transform* pParent, const Mode& mode);
	
	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::Invisible"> : 透明状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
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
	/// 取得可能状態か設定
	/// </summary>
	/// <param name="isRetrievable"> : 取得可能状態か</param>
	void SetIsRetrievable(const bool isRetrievable) { isRetrievable_ = isRetrievable; }

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
	void CanNotPlaceAnimation();

private:

	/// <summary>
	/// 取得可能アニメーション
	/// </summary>
	void RetrievableAnimation();

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

