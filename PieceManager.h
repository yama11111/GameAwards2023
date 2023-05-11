#pragma once
#include "Piece.h"

class PieceManager
{
public:
    // 関数
    PieceManager();
    void Update(void);
    void Draw(void);
private:
    // 変数
    std::vector<std::vector<Piece>> puzMat_;
    std::vector<std::unique_ptr<Piece>> piseses;

    //縦横の数を代入
    int BloickX;
    int BloickY;

public:
    // setter・getter
   // inline const std::vector<std::vector<Pises>>& GetPuzMat(void) { return puzMat_; }
};

