#pragma once
#include "Vector2.h"
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

	//プレイヤーかフィルターか
	bool chengeF = true;

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
	void Update();
	void Draw();

	//位置
	YMath::Vector2 GetPos() { return playerPos; };
	void SetPos(YMath::Vector2 nowpos) { playerPos = nowpos; };

	//最初の大きさ
	YMath::Vector2 GetSize() { return playerSize; };
	void SetSize(YMath::Vector2 nowsize) { playerPos = nowsize; };

	//今の大きさ
	YMath::Vector2 GetNowSizeX() { return playerCheckSizeRL; };
	YMath::Vector2 GetNowSizeY() { return playerCheckSizeUD; };

	bool GetmoveFlag() { return chengeF; };
	bool GetpassFlag() { return sukeF; };
	bool GetcornerFlag() { return kadoF; };

	void SetmoveFlag(bool flag) { chengeF = flag; };
	void SetpassFlag(bool flag) { sukeF = flag; };
	void SetcornerFlag(bool flag) { kadoF = flag; };
};