#pragma once
#include "IBlock.h"
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

public:
    // �֐�
    Sign(const Vector2& mapchipSize);

    void Update(void);
    void Draw(void);

    // �p�[�t�F�N�g�s�N�Z���R���W����
    void PPC(YukiMapchipCollider* ptr);

    // �ϐ�
    std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip_{};
};

