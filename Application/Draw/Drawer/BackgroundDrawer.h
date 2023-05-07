#pragma once
#include "ParticleManager.h"
#include "SkydomeDrawer.h"
#include "TowerDrawer.h"

class BackgroundDrawerCommon
{

protected:

	// 静的パーティクルマネージャーポインタ
	static YGame::ParticleManager* spParticleMan_;

	
	// 背景マテリアル
	static std::unique_ptr<YGame::Material> sBackMate_;


	// 統一用フラグ
	static bool sIsUnify_;

	// アンビエント統一用タイマー
	static YMath::Timer sUnifyTim_;

	// アンビエント統一イージング
	static YMath::Ease<YMath::Vector3> sUnifyAmbientEas_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan);

	/// <summary>
	/// 静的リセット
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();

public:

	/// <summary>
	/// 統一
	/// </summary>
	static void StaticUnify();

public:

	virtual ~BackgroundDrawerCommon() = default;

};

class BackgroundDrawer :
	private BackgroundDrawerCommon
{

private:

	// タワー
	struct Tower
	{
		// 親トランスフォーム
		YGame::Transform transform_;

		// 描画クラス
		TowerDrawer drawer_;
	};

private:

	// タワーリスト
	std::list<std::unique_ptr<Tower>> towers_;

	// スカイドーム
	YGame::Transform skydome_;

	// スカイドーム描画クラス
	SkydomeDrawer skydomeDra_;


	// 泡グリッド発生用タイマー
	YMath::Timer emitBubbleGridTim_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// リセット
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

private:

	/// <summary>
	/// タワー初期化
	/// </summary>
	void InitializeTowers();

	/// <summary>
	/// エミッター更新
	/// </summary>
	void UpdateEmitter();

	/// <summary>
	/// 泡グリッド発生
	/// </summary>
	void EmitBubbleCharacter();
};

