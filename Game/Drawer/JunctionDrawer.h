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
		eRed, // 赤
		eEnd, // リサイズ用
	};

protected:

	// パーツの総数
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// 種類の総数
	static const size_t sTypeNum_ = static_cast<size_t>(Type::eEnd);

	// 枠の総数
	static const size_t sFrameNum_ = 3;

protected:

	// ----- 接合部 ----- //

	// モデル (パーツの数だけ)
	static std::array<std::array<YGame::Model*, sPartsNum_>, sTypeNum_> spModels_;

	// モデル (グリッド)
	static YGame::Model* spGridModel_;
	
	// モデル (線)
	static YGame::Model* spRayModel_;

	// ----- アニメーション ----- //

	// 立ち回転スピードイージング
	static YMath::Ease<float> sIdleRotaSpeedEase_;

	
	// 接続時プッシュ大きさ係数イージング
	static YMath::Ease<float> sConnectPushScaleFactorEase_;

	// 接続時レイ大きさ係数イージング
	static YMath::Ease<float> sConnectRayScaleEase_;


	// 接続位置係数イージング
	static YMath::Ease<float> sConnectPosFactorEase_;

	// 接続位置係数イージング
	static YMath::Ease<float> sConnectRotaFactorEase_;

	// 接続回転スピードイージング
	static YMath::Ease<float> sConnectRotaSpeedEase_;

	// 接続大きさイージング
	static YMath::Ease<YMath::Vector3> sConnectScaleEase_;

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
	std::array<std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_>, sFrameNum_> modelObjs_;

	// モデル用オブジェクト (グリッド)
	std::unique_ptr<YGame::Model::Object> gridModelObjs_;

	// モデル用オブジェクト (線)
	std::unique_ptr<YGame::Model::Object> rayModelObjs_;

	// 向き
	YMath::Vector3 direction_;
	
	// 向き
	YMath::Vector3 initDirection_;

	// 種類
	Type type_ = Type::eGreen;

	// 種類インデックス
	size_t typeIndex_ = 0;

	// 接続先
	JunctionDrawer* pPartner_ = nullptr;

	// ----- 演出 ----- //

	// 動いているか
	bool isAct_ = false;

	
	// 位置 (アニメ用)
	std::array<YMath::Vector3, sFrameNum_> animePoss_;
	
	// 回転 (アニメ用)
	std::array<YMath::Vector3, sFrameNum_> animeRotas_;
	
	// 大きさ (アニメ用)
	std::array<YMath::Vector3, sFrameNum_> animeScales_;


	// 位置 (アニメ用)
	YMath::Vector3 animeRayPos_;

	// 回転 (アニメ用)
	YMath::Vector3 animeRayRota_;

	// 大きさ (アニメ用)
	YMath::Vector3 animeRayScale_;


	// 立ちモーションか
	bool isIdle_ = false;

	// 立ちタイマー
	std::array<YMath::Timer, sFrameNum_> idleTimers_;


	// 接続したか
	bool isConnected_ = false;

	// 接続タイマー
	YMath::Power connectPower_;


	// 向き合わせタイマー
	YMath::Timer alignDirectionTimer_;

	// 向き合わせイージング
	YMath::Ease<YMath::Vector3> alignDirectionEase_;
	
	// レイスケールタイマー
	YMath::Power rayScalePower_;

	bool isSelect_ = false;
	
	bool isPass_ = false;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="direction"> : 向き</param>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eGreen"> : 緑</param>
	/// <param name="BlockDrawerCommon::Type::eRed"> : 赤</param>
	void Initialize(YGame::Transform* pParent, const YMath::Vector3& direction, const Type& type);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="direction"> : 向き</param>
	/// <param name="Type"> : 種類</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eGreen"> : 緑</param>
	/// <param name="BlockDrawerCommon::Type::eRed"> : 赤</param>
	void Reset(const YMath::Vector3& direction, const Type& type);

	void Reset();

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
	
	//
	void AnimatePass(const bool isPass);
	
	/// <summary>
	/// 接続
	/// </summary>
	/// <param name="pPartner"> : 接続先のポインタ</param>
	void AnimateConnection(JunctionDrawer* pPartner);
	
	
	void AnimateSelectConnect(const bool isSelect);

private:

	/// <summary>
	/// 立ちモーション更新
	/// </summary>
	void UpdateIdleAnimation();

	/// <summary>
	/// 接続モーション更新
	/// </summary>
	void UpdateConnectAnimation();
	
	void UpdateSelectAnimation();

public:

	~JunctionDrawer() = default;
};

