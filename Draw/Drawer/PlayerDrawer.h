#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// プレイヤー描画用コモンクラス
class PlayerDrawerCommon
{
protected:
	// パーツの名前
	enum class Parts
	{
		Body, // 体
	};
protected:
	// パーツの総数
	static const size_t PartsNum_ = 2;
protected:
	// モデル (パーツの数だけ)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// プレイヤー描画用クラス
class PlayerDrawer :
	private PlayerDrawerCommon,
	private YGame::SlimeActor
{
private:
	// トランスフォーム 
	std::unique_ptr<YGame::Transform> core_;
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	// 色
	std::unique_ptr<YGame::Color> color_;

	// 向きポインタ
	YMath::Vector3* pDirection_ = nullptr;
	// 立ちモーション用タイマー
	YMath::Timer idelTim_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親行列ポインタ (この行列に追従する)</param>
	/// <param name="pDirection"> : 向きポインタ (この向きに向く)</param>
	void Initialize(YMath::Matrix4* pParent, YMath::Vector3* pDirection);
	// リセット (中身だけ初期化)
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	// 立ちモーション
	void IdleAnimation();
	// ジャンプモーション
	void JumpAnimation();
	// 着地モーション
	void LandingAnimation();
	// 色替えアニメーション
	//void ChangeColor(const );
};

