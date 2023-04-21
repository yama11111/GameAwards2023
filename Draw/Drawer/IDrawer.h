#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
#include <memory>

// 描画基底クラス
class IDrawer : protected YGame::SlimeActor
{
public:
	
	// 状態
	enum class Mode
	{
		Normal	  = 0, // 通常
		Red		  = 1, // 赤
		Invisivle = 2, // 透明
		None, // 無し
	};
	
	// モードの数
	static const size_t ModeNum_ = 3;

protected:
	
	// トランスフォーム 
	std::unique_ptr<YGame::Transform> core_;
	
	// 現在の状態
	Mode current_ = Mode::Normal;
	
	// 立ちモーション用タイマー
	YMath::Timer idleTim_;
	
	// 親ポインタ
	YGame::Transform* pParent_ = nullptr;

protected:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親トランスフォーム</param>
	/// <param name="mode"> : 現在の状態</param>
	/// <param name="intervalTime"> : 立ちモーションの間隔</param>
	void Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime);

	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="mode"> : 現在の状態</param>
	void Reset(const Mode& mode);

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
	
	// 静的カメラポインタ
	static YGame::Camera* spCamera_;

	// 静的パーティクルマネージャーポインタ
	static YGame::ParticleManager* spParticleMan_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pCamera"> : カメラポインタ</param>
	/// <param name="pParticleMan"> : パーティクルマネージャーポインタ</param>
	static void StaticInitialize(YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~IDrawer() = default;
};

