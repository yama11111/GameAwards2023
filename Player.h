#pragma once
#include "Keys.h"
#include "PlayerDrawer.h"

class Player
{
private:

	// プレイヤー
	YGame::Transform player_;

	// 向き
	YMath::Vector3 direction_;

	// プレイヤー描画クラス
	PlayerDrawer playerDra_;

	//スタート時のPos格納
	YMath::Vector3 startPos = { 0.0f,0.0f,0.0f };

	//プレイヤーがすり抜けるか
	bool ClearFlag = false;

	//フィルターの角に当たっているかどうか
	bool CornerFlag = false;

public:

	//インクリメント
	Player();

	//デクリメント
	~Player();

	//初期化
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	//更新
	void Update(YGame::Transform filterPos, YMath::Vector2 filterSizeLR, YMath::Vector2 filterSizeUD);
	void Update(YGame::Transform filterPos);

	//Pre描画(フィルターの前)
	void PreDraw();

	//Post描画(フィルターの後)
	void PostDraw();

	//リセット
	void Reset();

	//GetFlag関数
	bool GetClearFlag() { return ClearFlag; };
	bool GetCornerFlag() { return CornerFlag; };

	//SetFlag関数
	void SetClearFlag(bool flag) { ClearFlag = flag; };
	void SetCornerFlag(bool flag) { CornerFlag = flag; };

	//CengeFlag関係
	void ChengeClearFlag() { ClearFlag = !ClearFlag; };
	void ChengeCornerFlag() { CornerFlag = !ClearFlag; };

	//direction関係
	void SetDirection(YMath::Vector3 direction) { direction_ = direction; };
	YMath::Vector3 GetDirection() { return direction_; };

	//ジャンプ関係
	bool JumpFlag = false;
	float JumpPower = 0;
	float Jump = 0;

	//重力関係
	float Gravity = 0;
	float GravityPower = 0;
};