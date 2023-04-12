#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
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
	// 変更後の状態
	Mode next_ = Mode::None;
	
	// 立ちモーション用タイマー
	YMath::Timer idleTim_;
	
	// 親ポインタ
	YGame::Transform* pParent_ = nullptr;
protected:
	// 初期化
	void Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime);
	// リセット
	void Reset(const Mode& mode);
	// 更新
	void Update(const YGame::Transform::Status& status);
protected:
	// 立ちモーション
	virtual void IdleAnimation() = 0;
protected:
	// 静的パーティクルマネージャーポインタ
	static YGame::ParticleManager* spParticleMan_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ParticleManager* pParticleMan);
public:
	virtual ~IDrawer() = default;
};

