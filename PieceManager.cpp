#include "PieceManager.h"

//
PieceManager::PieceManager()
{
	//�c����
	BloickX = 9;
	BloickY = 9;

	//�����̃s�[�X����
	for (int i = 0; i < BloickX * BloickY; i++)
	{
		//����
		std::unique_ptr<Piece> newPises;
		newPises.reset(new Piece());

		//������
		newPises->Initialize();

		//pos
		YMath::Vector3 pos = { 0,0,0 };

		//
		newPises->SetPos(pos);

		//�i�[
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
