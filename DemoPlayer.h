#pragma once
#include "PlayerDrawer.h"
#include "MapChip.h"
#include "Keys.h"

class DemoPlayer : public YGame::MapChipCollider
{

private:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// スピード
	YMath::Vector3 speed_;

	// 向き
	YMath::Vector3 direction_;

	// 描画クラス
	PlayerDrawer drawer_;

	// ジャンプ回数
	int jumpCount_ = 0;

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

public:

	/// <summary>
	// 位置取得 (参照)
	/// </summary>
	/// <returns></returns>
	YMath::Vector3& PosRef() override { return transform_->pos_; }

	/// <summary>
	// スピード取得 (参照)
	/// </summary>
	/// <returns></returns>
	YMath::Vector3& SpeedRef() override { return speed_; }

private:

	// キー
	static YInput::Keys* spKeys_;

	// マップチップ
	static YGame::MapChip* spMapChip_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();
	
	/// <summary>
	/// 静的マップチップポインタ設定
	/// </summary>
	/// <param name="pMapChip"> : マップチップポインタ</param>
	static void StaticSetMapChip(YGame::MapChip* pMapChip);
	
};

