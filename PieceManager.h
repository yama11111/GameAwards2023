#pragma once
#include "Piece.h"

class PieceManager
{
public:
    // �֐�
    PieceManager();
    void Update(void);
    void Draw(void);
private:
    // �ϐ�
    std::vector<std::vector<Piece>> puzMat_;
    std::vector<std::unique_ptr<Piece>> piseses;

    //�c���̐�����
    int BloickX;
    int BloickY;

public:
    // setter�Egetter
   // inline const std::vector<std::vector<Pises>>& GetPuzMat(void) { return puzMat_; }
};

