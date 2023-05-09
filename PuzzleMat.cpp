#include "PuzzleMat.h"

PuzzleMat::PuzzleMat(int pieceX, int pieceY)
{
    for (int y = 0; y < pieceY; y++) 
    {
        puzMat_.emplace_back(std::vector<Pises>{});

        for (int x = 0; x < pieceX; x++)
        {
            puzMat_[y].emplace_back(Pises{});
            puzMat_[y][x].Initialize(x,y);
        }
    }
}

void PuzzleMat::Update(void)
{
    for (auto y = 0; y < puzMat_.size(); y++)
    {
        for (auto x= 0; x < puzMat_[0].size(); x++)
        {
            puzMat_[y][x].Update();
        }
    }
}

void PuzzleMat::Draw(void)
{
    for (auto y = 0; y < puzMat_.size(); y++)
    {
        for (auto x = 0; x < puzMat_[0].size(); x++)
        {
            puzMat_[y][x].Draw();
        }
    }
}

//複数のピース生成
for (int i = 0; i < 2; i++)
{
    //生成
    std::unique_ptr<Pises> newPises;
    newPises.reset(new Pises());

    //初期化
    newPises->Initialize({ i * 20.0f,5.0f,0.0f }, {}, {});

    //格納
    piseses.push_back(std::move(newPises));
}