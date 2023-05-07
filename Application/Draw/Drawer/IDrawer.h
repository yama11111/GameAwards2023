#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
#include <memory>

// 描画基底クラス
class IDrawer : protected YGame::SlimeActor
{

protected:

	// トランスフォーム 
	std::unique_ptr<YGame::Transform> core_;
	
	// 親ポインタ
	YGame::Transform* pParent_ = nullptr;
	
	// 立ちモーション用タイマー
	YMath::Timer idleTim_;

protected:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親トランスフォーム</param>
	/// <param name="intervalTime"> : 立ちモーションの間隔</param>
	void Initialze(YGame::Transform* pParent, const UINT intervalTime);

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="status"></param>
	void Update(const YGame::Transform::Status& status);

protected:

	/// <summary>
	/// 立ちモーション
	/// </summary>
	virtual void IdleAnimation() = 0;

protected:
	
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

	// マテリアルポインタ
	static YGame::Material* spMate_;

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
	/// <param name="pCamera"> : カメラポインタ</param>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(
		YGame::ViewProjection* pVP, 
		YGame::Material* pMate, 
		YGame::Camera* pCamera, 
		YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~IDrawer() = default;
};

