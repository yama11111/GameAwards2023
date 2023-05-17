#pragma once
#include <map>
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

    static constexpr float blockRadius_{ 16.f }; // �u���b�N�̔��a

    static constexpr float pushOut_{ 0.2f }; // ����I�����o�����̈ړ���
    static constexpr float springPower_{ 5.f }; // �o�l�u���b�N�̃W�����v��
    static constexpr float springFall_{ 0.5f }; // �o�l�u���b�N���̗������x

    enum class BlockType // �u���b�N�̎��
    {
        NONE,
        BASIC,

        SPRING,

        WARP1,
        WARP2,
    };

    enum class Direction
    {
        TOP,
        RIGHT,
        LEFT,
        BOTTOM,
    };

    struct Vec2Int
    {
        size_t x_{};
        size_t y_{};
    };

    struct WarpIdx
    {
        // �������ڑ��ς݂� - ��
        bool isConnected_{};
        // �������̏o���ʒu - �s��
        Direction dirMe_{};

        // �����"�u���b�N"�̔z��v�f���i�ŔɋA���j - �s��
        Vec2Int mapchipElemPartner_{};
        // �����"�Ŕ�"�̔z��v�f���istage�ɋA���j - �s��
        size_t IdxSign_{};
        // ���葤�̏o���ʒu - �s��
        Direction dirPartner_{};
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
    std::map<WarpIdx, Vec2Int> warpInfos_{};
    
    // ��_�i����j���W
    Vector3 topLeftPos_{}; // z�͏��0
};

