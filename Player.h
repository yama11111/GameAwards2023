#pragma once
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
	
public:

	//インクリメント
	Player();

	//デクリメント
	~Player();

	//初期化
	void Initialize();

	//更新
	void Update();

	// 描画
	void Draw();

	//リセット
	void Reset();

	// 着地
	void Landing() { playerDra_.LandingAnimation(); }

	//Vector3に代入
	void SetPos(YMath::Vector3 pos) { player_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { player_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { player_.rota_ = rot; };

	//Vector3を入手
	YMath::Vector3 GetPos() { return player_.pos_; };
	YMath::Vector3 GetScale() { return player_.scale_; };
	YMath::Vector3 GetRot() { return player_.rota_; };

	//Transformを入手
	YGame::Transform GetTransform() { return player_; };

	//direction関係
	void SetDirection(YMath::Vector3 direction) { direction_ = direction; };
	YMath::Vector3 GetDirection() { return direction_; };
};