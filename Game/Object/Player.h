#pragma once
#include "PlayerDrawer.h"
#include "CollisionPrimitive.h"

// インクルード回避用
namespace YInput { class Keys; }

class Player :
	public YGame::Box2D
{

private:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// スピード
	YMath::Vector3 speed_;

	// 向き
	YMath::Vector3 direction_;

	// ジャンプ回数
	int jumpCount_ = 0;
	
	// 描画クラス
	PlayerDrawer drawer_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos"> : 初期位置</param>
	void Initialize(const YMath::Vector3& pos);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="pos"> : 初期位置</param>
	void Reset(const YMath::Vector3& pos);

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
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();

	/// <summary>
	/// 物理挙動更新
	/// </summary>
	void UpdatePhysics();

private:

	// キー
	static YInput::Keys* spKeys_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();


};

