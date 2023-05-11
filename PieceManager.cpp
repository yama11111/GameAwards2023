#include "PieceManager.h"

//
PieceManager::PieceManager()
{
	//縦横数
	BloickX = 9;
	BloickY = 9;

	//複数のピース生成
	for (int i = 0; i < BloickX * BloickY; i++)
	{
		//生成
		std::unique_ptr<Piece> newPises;
		newPises.reset(new Piece());

		//初期化
		newPises->Initialize();

		//pos
		YMath::Vector3 pos = { 0,0,0 };

		//
		newPises->SetPos(pos);

		//格納
		piseses.push_back(std::move(newPises));
	}
}

void PieceManager::Update(void)
{
	for (size_t i = 0; i < piseses.size(); i++)
	{
		piseses[i]->Update();
	}
}

void PieceManager::Draw(void)
{
	for (size_t i = 0; i < piseses.size(); i++)
	{
		piseses[i]->Draw();
	}
}
