#pragma once
#include "Vector2.h"
#include "Block.h"
#include "BlockDrawer.h"

class Pises
{
private:
	// フィルター
	YGame::Transform pises_;

	// ブロック描画クラス
	BlockDrawer blockDra_;

	//ブロック格納用変数
	std::vector<std::unique_ptr<Block>> blocks;

	//XY
	const int blockX = 9;
	const int blockY = 9;

	int map[81] =
	{
		1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,1,
		1,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,0,1,
		1,1,0,0,0,0,1,1,1,
		1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,
	};

	//右回転中
	bool RotR = false;

public:
	//インクリメント
	Pises();

	//デクリメント
	~Pises();

	//初期化
	void Initialize();
	void Initialize(int x, int y);
	void Initialize(YMath::Vector3 pos, YMath::Vector3 rot, YMath::Vector3 scale);

	//ピース選択
	void ChoosePises(bool vec);

	//更新
	void Update(bool nowmode);

	//描画
	void Draw();
	void DrawBlock();
	void DrawPiese();

	//これをfor文で呼び出してもらってmap分繰り返す
	void CreateBlock(int mode, YGame::Transform pises, int number);

	//Vector3に代入
	void SetPos(YMath::Vector3 pos) { pises_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { pises_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { pises_.rota_ = rot; };

	//右回転
	void SerRotRight(bool flag) { RotR = flag; };
};

