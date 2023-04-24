#pragma once
#include "ParticleManager.h"
#include "SkydomeDrawer.h"
#include "TowerDrawer.h"

class BackgroundDrawerCommon
{

protected:

	// 静的パーティクルマネージャーポインタ
	static YGame::ParticleManager* spParticleMan_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(YGame::ParticleManager* pParticleMan);

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

public:

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
	void EmitBubbleGrid();
};

