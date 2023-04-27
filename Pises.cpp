#include "Pises.h"
#include "imgui.h"

Pises::Pises()
{

}

Pises::~Pises()
{

}

void Pises::Initialize()
{
	//transform初期化
	pises_.Initialize({ {-5.0f,10.0f,0.0f}, {}, {4.5f,4.5f,0.5f} });
	blockDra_.Initialize(&pises_, IMode::Type::Normal);

	//総ブロック数
	int count = blockX * blockY;

	//ブロックを作る
	for (int i = 0; i < count; i++)
	{
		CreateBlock(map[i], pises_, i);
	}
}

void Pises::Initialize(YMath::Vector3 pos, YMath::Vector3 rot, YMath::Vector3 scale)
{
	//transform初期化
	pises_.Initialize({ pos,rot, {4.5f,4.5f,0.5f} });
	blockDra_.Initialize(&pises_, IMode::Type::Normal);

	//総ブロック数
	int count = blockX * blockY;

	//ブロックを作る
	for (int i = 0; i < count; i++)
	{
		CreateBlock(map[i], pises_, i);
	}
}

void Pises::Update()
{

	// ピースの更新
	pises_.UpdateMatrix();
	blockDra_.Update();

	//ブロックの更新
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Update();
	}
}

//両方描画
void Pises::Draw()
{
	//ピースの描画
	blockDra_.Draw();

	//ブロックの描画
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Draw();
	}
}

//ブロックのみ描画
void Pises::DrawBlock()
{
	//ブロックの描画
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Draw();
	}
}

//ピースのみ描画
void Pises::DrawPiese()
{
	//ピースの描画
	blockDra_.Draw();
}

//ブロック生成
void Pises::CreateBlock(int mode, YGame::Transform pises, int number)
{
	//縦横
	int x = number;
	int y = number;

	//位置を計算で

	y = number / blockX;
	x = number - (y * blockY);

	//mode格納
	int nowmode = mode;

	//サイズ
	float harfsize = 1.0f;

	//格納用Vector
	YMath::Vector3 result;

	//生成
	std::unique_ptr<Block> newBlock;
	newBlock.reset(new Block());

	//初期化
	newBlock->Initialize();

	//種類を格納
	newBlock->SetKind(nowmode);

	//ピースのposを格納
	result = pises_.pos_;

	//左上に位置を調整
	result.x_ -= pises_.scale_.x_ + (harfsize * 3) + (harfsize / 2);
	result.y_ += pises_.scale_.y_ + (harfsize * 3) + (harfsize / 2);

	//pos
	result.x_ += x * (harfsize * 2);
	result.y_ -= y * (harfsize * 2);
	result.z_ = 0;

	//pos格納 
	newBlock->SetPos(result);

	//scaleほぼこれでいい
	result = { harfsize / 2,harfsize / 2,harfsize };

	////scale格納
	newBlock->SetScale(result);

	//格納
	blocks.push_back(std::move(newBlock));
}
