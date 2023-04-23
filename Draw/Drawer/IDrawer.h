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
	};
	
protected:

	// トランスフォーム 
	std::unique_ptr<YGame::Transform> core_;
	
	// 親ポインタ
	YGame::Transform* pParent_ = nullptr;
	
	// 立ちモーション用タイマー
	YMath::Timer idleTim_;

private:
	
	// 現在の状態
	Mode current_ = Mode::Normal;

	// 現在の状態番号
	size_t currentIdx_ = 0;

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
	
	/// <summary>
	/// 現在の状態番号取得
	/// </summary>
	/// <returns>現在の状態番号</returns>
	size_t CurrentModeIndex() { return currentIdx_; }
	
	/// <summary>
	/// 現在の状態取得
	/// </summary>
	/// <returns>現在の状態</returns>
	Mode CurrentMode() { return current_; }

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="mode"> : 状態</param>
	void ChangeMode(const Mode& mode);

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

