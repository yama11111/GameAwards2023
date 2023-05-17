#pragma once
#include <vector>
#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"

#include "YukiMapchipCollider.h"

class Sign
{
protected:
    // ��`
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;

    static constexpr float pushOut_{ 0.2f };
    static constexpr float blockRadius_{ 16.f };

    enum class BlockType
    {
        NONE,
        BASIC,
    };

public:
    // �֐�
    Sign(const Vector2& mapchipSize);

    void Update(void);
    void Draw(void);

    // �p�[�t�F�N�g�s�N�Z���R���W����
    void PPC(YukiMapchipCollider* ptr);
    const Vector2& CalcVelStuck(const Vector2& pointPos); // �ړ����͂Ȃ��̉����o���l�v�Z�֐� ��Move�̑O�Ɏg�� =>���g���ĂȂ�
    const Vector2& CalcVelMove(const Vector2& pointPos, const Vector2& vel); // �ړ����͂���̉����o���l�v�Z�֐� ��Stuck�̌�Ɏg��

    // �ϐ�
    //std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip2_{};
    std::vector<std::vector<int>> mapchip_{};
    
    // ��_�i����j���W
    Vector3 topLeftPos_{}; // z�͏��0
};

