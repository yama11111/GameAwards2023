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

//�����̃s�[�X����
for (int i = 0; i < 2; i++)
{
    //����
    std::unique_ptr<Pises> newPises;
    newPises.reset(new Pises());

    //������
    newPises->Initialize({ i * 20.0f,5.0f,0.0f }, {}, {});

    //�i�[
    piseses.push_back(std::move(newPises));
}