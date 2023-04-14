#pragma once
#include "PlayerDrawer.h"
#include "FilterDrawer.h"

class Player
{
private:

	// プレイヤー
	YGame::Transform player_;

	// 向き
	YMath::Vector3 direction_;

	// プレイヤー描画クラス
	PlayerDrawer playerDra_;
	FilterDrawer filterDra_;

	//スタート時のPos格納
	YMath::Vector3 startPos = { 0.0f,0.0f,0.0f };

	//移動量格納
	YMath::Vector3 movePos = { 0.0f,0.0f,0.0f };

	//操作してるかどうか
	bool PlayFlag = true;

	//プレイヤーがすり抜けるか
	bool ClearFlag = false;

	//フィルターの角に当たっているかどうか
	bool CornerFlag = false;

	//ジャンプ関係
	bool JumpFlag = false;
	float JumpPower = 0;
	float Jump = 0;

	//重力関係
	float Gravity = 0;
	float GravityPower = 0;
public:

	//インクリメント
	Player();

	//デクリメント
	~Player();

	//初期化
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	//更新
	//void Update(YGame::Transform filterPos, YMath::Vector2 filterSizeLR, YMath::Vector2 filterSizeUD);
	void Update(YGame::Transform filterPos);
	void Update();

	//Pre描画(フィルターの前)
	void PreDraw();

	//Post描画(フィルターの後)
	void PostDraw();

	//リセット
	void Reset();

	//重力関係のリセット
	void JumpReset();

	//重力、ジャンプの力を加算
	void AddGravity();

	// 着地
	void Landing() { playerDra_.LandingAnimation(); }

	//GetFlag関数
	bool GetClearFlag() { return ClearFlag; };
	bool GetCornerFlag() { return CornerFlag; };
	bool GetJumpFlag() { return JumpFlag; };
	bool GetPlayFlag() { return PlayFlag; };

	//SetFlag関数
	void SetClearFlag(bool flag) { ClearFlag = flag; };
	void SetCornerFlag(bool flag) { CornerFlag = flag; };
	void SetJumpFlag(bool flag) { JumpFlag = flag; };
	void SetPlayFlag(bool flag) { PlayFlag = flag; };

	//CengeFlag関係
	void ChengeClearFlag() { ClearFlag = !ClearFlag; };
	void ChengeCornerFlag() { CornerFlag = !CornerFlag; };
	void ChengeJumpFlag() { JumpFlag = !JumpFlag; };
	void ChengePlayFlag() { PlayFlag = !PlayFlag; };

	//Vector3に代入
	void SetPos(YMath::Vector3 pos) { player_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { player_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { player_.rota_ = rot; };
	void SetStartPos(YMath::Vector3 pos) { startPos = pos; };
	void SetMovePos(YMath::Vector3 pos) { movePos = pos; };
	void SetJumpPower(float power) { JumpPower = power; };
	void SetJump(float power) { Jump = power; };
	void SetGravityPower(float power) { GravityPower = power; };
	void SetGravity(float power) { Gravity = power; };

	//Vector3を入手
	YMath::Vector3 GetPos() { return player_.pos_; };
	YMath::Vector3 GetScale() { return player_.scale_; };
	YMath::Vector3 GetRot() { return player_.rota_; };
	YMath::Vector3 GetStartPos() { return startPos; };
	YMath::Vector3 GetMovePos() { return movePos; };
	float GetGravity() { return Gravity; };

	//すぐに移動
	void PlayerMove(YMath::Vector3 pos);

	//Transformを入手
	YGame::Transform GetTransform() { return player_; };

	//direction関係
	void SetDirection(YMath::Vector3 direction) { direction_ = direction; };
	YMath::Vector3 GetDirection() { return direction_; };
};