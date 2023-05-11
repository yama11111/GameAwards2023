#include "SpringBlock.h"

SpringBlock::SpringBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::SPRING);
}

void SpringBlock::Update(void)
{
}

void SpringBlock::Draw(void)
{
    //int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
    //int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

    //switch (GetRotate() / 90)
    //{
    //case 0:
    //    DrawTriangle(
    //        posX, posY - radiusY, // �ł��ς�
    //        posX - radiusX, posY + radiusY, // ����
    //        posX + radiusX, posY + radiusY, // �E��
    //        0x00ffff, true
    //    );
    //    break;
    //case 1:
    //    DrawTriangle(
    //        posX + radiusX, posY, // �ł��ς�
    //        posX - radiusX, posY - radiusY, // ����
    //        posX - radiusX, posY + radiusY, // �E��
    //        0x00ffff, true
    //    );
    //    break;
    //case 2:
    //    DrawTriangle(
    //        posX, posY + radiusY, // �ł��ς�
    //        posX - radiusX, posY - radiusY, // ����
    //        posX + radiusX, posY - radiusY, // �E��
    //        0x00ffff, true
    //    );
    //    break;
    //case 3:
    //    DrawTriangle(
    //        posX - radiusX, posY, // �ł��ς�
    //        posX + radiusX, posY - radiusY, // ����
    //        posX + radiusX, posY + radiusY, // �E��
    //        0x00ffff, true
    //    );
    //    break;
    //}

}
