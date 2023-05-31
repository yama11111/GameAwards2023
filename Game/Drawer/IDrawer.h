#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
#include "Audio.h"
#include <memory>

// 描画基底クラス
class IDrawer : protected YGame::SlimeActor
{

protected:

	// トランスフォーム 
	std::unique_ptr<YGame::Transform> core_;
	
	// 親ポインタ
	YGame::Transform* pParent_ = nullptr;

protected:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親トランスフォーム</param>
	void Initialze(YGame::Transform* pParent);

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="status"></param>
	void Update(const YGame::Transform::Status& status);

	/// <summary>
	/// ペアレントされているか取得
	/// </summary>
	/// <returns>ペアレントされているか</returns>
	bool GetIsParented() { return pParent_ != nullptr; }

protected:
	
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

	// マテリアルポインタ
	static YGame::CBMaterial* spMate_;

	// 光源ポインタ
	static YGame::CBLightGroup* spLightGroup_;

	// 静的カメラポインタ
	static YGame::Camera* spCamera_;

	// 静的パーティクルマネージャーポインタ
	static YGame::ParticleManager* spParticleMan_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	/// <param name="pMate"> : マテリアルポインタ</param>
	/// <param name="pLightGroup"> : 光源ポインタ</param>
	/// <param name="pCamera"> : カメラポインタ</param>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(
		YGame::ViewProjection* pVP, 
		YGame::CBMaterial* pMate, 
		YGame::CBLightGroup* pLightGroup, 
		YGame::Camera* pCamera, 
		YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~IDrawer() = default;
};

