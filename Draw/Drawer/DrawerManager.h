#pragma once
#include "ParticleManager.h"
#include "Camera.h"

class DrawerManager
{

public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	/// <param name="pCamera"> : カメラポインタ</param>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan);

};

