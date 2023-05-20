#pragma once
#include "IDrawer.h"
#include <array>

// スイッチ描画用コモンクラス
class SwitchDrawerCommon
{

public:

	// パーツの名前
	enum class Parts
	{
		eBaseOnCore, // 台座オン核
		eBaseOnShell, // 台座オン殻
		eBaseOffCore, // 台座オフ核
		eBaseOffShell, // 台座オフ殻
		eLeverCore, // レバー核
		eLeverShell, // レバー殻
		eEnd, // リサイズ用
	};

	// 種類
	enum class Type
	{
		eGreen, // 緑
		eRed, // 赤
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

protected:

	// ----- スイッチ ----- //

	// モデル (パーツの数だけ)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	
	// ----- アニメーション ----- //

	// スイッチオン回転スピードイージング
	static YMath::Ease<float> sSwitchOnRotaSpeedEase_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~SwitchDrawerCommon() = default;
};

// スイッチ描画用クラス
class SwitchDrawer :
	private IDrawer,
	private SwitchDrawerCommon
{

private:

	// ------ オブジェクト ------ // 

	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// 種類
	Type type_ = Type::eGreen;

	// 種類インデックス
	size_t typeIndex_ = 0;
	
	
	// ----- 演出 ----- //

	// 動いているか
	bool isAct_ = false;

	// 台座位置 (アニメ用)
	YMath::Vector3 animeBasePos_;
	

	// レバー位置 (アニメ用)
	YMath::Vector3 animeLeverPos_;

	// レバー回転 (アニメ用)
	YMath::Vector3 animeLeverRota_;


	// スイッチオンか
	bool isSwitchOn_ = false;

	// スイッチオンパワー
	YMath::Power switchOnPower_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eGreen"> : 緑</param>
	/// <param name="BlockDrawerCommon::Type::eRed"> : 赤</param>
	void Initialize(YGame::Transform* pParent, const Type& type);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eGreen"> : 緑</param>
	/// <param name="BlockDrawerCommon::Type::eRed"> : 赤</param>
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

	/// <summary>
	/// スイッチ
	/// </summary>
	/// <param name="isSwitchOn"> : 動かすか</param>
	void AnimateSwitch(const bool isSwitchOn);

private:

	/// <summary>
	/// スイッチアニメーション
	/// </summary>
	void UpdateSwitchAnimation();

public:

	~SwitchDrawer() = default;
};
