//#include "PuzzleMat.h"
//
//PuzzleMat::PuzzleMat(int pieceX, int pieceY)
//{
//    for (int y = 0; y < pieceY; y++) 
//    {
//        puzMat_.emplace_back(std::vector<Pises>{});
//
//        for (int x = 0; x < pieceX; x++)
//        {
//            puzMat_[y].emplace_back(Pises{});
//            puzMat_[y][x].Initialize();
//        }
//    }
//}
//
//void PuzzleMat::Update(void)
//{
//    for (auto y = 0; y < puzMat_.size(); y++)
//    {
//        for (auto x= 0; x < puzMat_[0].size(); x++)
//        {
//            puzMat_[y][x].Update();
//        }
//    }
//}
//
//void PuzzleMat::Draw(void)
//{
//    for (auto y = 0; y < puzMat_.size(); y++)
//    {
//        for (auto x = 0; x < puzMat_[0].size(); x++)
//        {
//            puzMat_[y][x].Draw();
//        }
//    }
//}
