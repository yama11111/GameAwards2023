#pragma once
#include "ObjectCollider.h"
#include "Transform.h"
#include "Audio.h"
#include <memory>

class Stage;

class IObject :
	public ObjectCollider
{

protected:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// 1F前の左上
	YMath::Vector3 elderLeftTop_;

public:

	/// <summary>
	/// 左上更新
	/// </summary>
	void UpdateLeftTop();

	/// <summary>
	/// 判定前更新
	/// </summary>
	virtual void PreUpdate() = 0;
	
	/// <summary>
	/// 判定後更新
	/// </summary>
	virtual void PostUpdate() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

public:

	void StopWarpSE() { spWarpSE_->Stop(); }
	void PlayWarpSE() { spWarpSE_->Play(false); }

public:

	virtual ~IObject() = default;

protected:

	// 静的ステージマネージャーポインタ
	static Stage* spStageMan_;

	static YGame::Audio* spWarpSE_;

public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pStageMan"> : ステージマネージャーポインタ</param>
	static void StaticInitialize(Stage* pStageMan);

};

