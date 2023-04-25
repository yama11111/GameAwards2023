#pragma once
#include "ParticleManager.h"
#include "Camera.h"

class DrawerHelper
{

private:

	// デフォルトマテリアル
	static std::unique_ptr<YGame::Material> sDefMate_;


	// クリアフラグ
	static bool sIsClear_;

	// 前回クリアフラグ
	static bool sIsElderClear_;

public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	/// <param name="pCamera"> : カメラポインタ</param>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan);

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
	/// クリア
	/// </summary>
	static void StaticClear() { sIsClear_ = true; }

};

