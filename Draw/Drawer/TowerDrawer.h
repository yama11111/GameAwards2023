#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"
#include <array>
#include <memory>

// タワー描画用コモンクラス
class TowerDrawerCommon
{

public:
	
	// 状態
	enum class Mode
	{
		Normal, // 通常
		Red, // 赤
	};
	
	// パーツの名前
	enum class Parts
	{
		Core, // 核
		Shell, // 殻
	};

protected:

	// モードの数
	static const size_t ModeNum_ = 2;
	
	// パーツの総数
	static const size_t PartsNum_ = 2;

protected:
	
	// モデル (パーツの数だけ)
	static std::array<std::array<YGame::Model*, PartsNum_>, ModeNum_> spModels_;
	
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

	// マテリアルポインタ
	static YGame::Material* spMate_;


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

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	/// <param name="pMate"> : マテリアルポインタ</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Material* pMate);

	/// <summary>
	/// 静的リセット
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();

public:
	
	virtual ~TowerDrawerCommon() = default;

};

// タワー描画用クラス
class TowerDrawer :
	private TowerDrawerCommon
{
private:
	
	// 核
	std::unique_ptr<YGame::Transform> core_;
	
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	

	// 状態
	Mode mode_ = Mode::Normal;

	// 状態番号
	size_t modeIdx_ = 0;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親行列ポインタ (この行列に追従する)</param>
	/// <param name="mode"> : 状態</param>
	void Initialize(YMath::Matrix4* pParent, const Mode& mode);
	
	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="mode"> : 状態</param>
	void Reset(const Mode& mode);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

};

