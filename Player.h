#pragma once
#include "Keys.h"
#include "PlayerDrawer.h"

class Player
{
private:
	YMath::Vector2 playerPos = { 0,0 };
	YMath::Vector2 playerSize = { 16,32 };

	YMath::Vector2 playerCheckPos = { 0,0 };
	YMath::Vector2 playerCheckSize = { 16,64 };

	YMath::Vector2 playerCheckSizeRL = { 16,64 };
	YMath::Vector2 playerCheckSizeUD = { 16,64 };

	//キーが押されているかどうか
	YMath::Vector2 DS;
	YMath::Vector2 AW;

	//プレイヤーがすり抜けるか
	bool sukeF = false;
	//passFlag

	//フィルターの角に当たっているかどうか
	bool kadoF = false;
	//corner
public:

	// プレイヤー
	YGame::Transform player_;
	// 向き
	YMath::Vector3 direction_;
	// プレイヤー描画クラス
	PlayerDrawer playerDra_;

	Player();
	~Player();

	void Inilialize();
	void Update(YGame::Transform filterPos, YMath::Vector2 filterSizeLR, YMath::Vector2 filterSizeUD);
	void Draw();
	void Reset();

	//位置
	YMath::Vector2 GetPos() { return playerPos; };
	void SetPos(YMath::Vector2 nowpos) { playerPos = nowpos; };

	//最初の大きさ
	YMath::Vector2 GetSize() { return playerSize; };
	void SetSize(YMath::Vector2 nowsize) { playerPos = nowsize; };

	//今の大きさ
	YMath::Vector2 GetNowSizeX() { return playerCheckSizeRL; };
	YMath::Vector2 GetNowSizeY() { return playerCheckSizeUD; };

	bool GetsukeFlag() { return sukeF; };
	bool GetkadoFlag() { return kadoF; };

	void SetsukeFlag(bool flag) { sukeF = flag; };
	void SetkadoFlag(bool flag) { kadoF = flag; };

	bool JumpFlag = false;
	float JumpPower = 0;
	float Jump = 0;

	float Gravity = 0;
	float GravityPower = 0;
};