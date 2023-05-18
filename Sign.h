#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
#include "BlockDrawer.h"

#include "YukiMapchipCollider.h"

namespace maruyama {
    class Sign
    {
    protected:
        // ��`
        using Vector2 = YMath::Vector2;
        using Vector3 = YMath::Vector3;
        using Vector4 = YMath::Vector4;
        using Transform = YGame::Transform;

        static constexpr float blockRadius_{ 2.f }; // �u���b�N�̔��a

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

        struct Vec2Int_t
        {
            size_t x_{};
            size_t y_{};
        };

        struct WarpIdx_t
        {
            // �������ڑ��ς݂� - ��
            bool isConnected_{};
            // �������̏o���ʒu - �s��
            Direction dirMe_{};

            // �����"�u���b�N"�̔z��v�f���i�ŔɋA���j - �s��
            Vec2Int_t mapchipElemPartner_{};
            // �����"�Ŕ�"�̔z��v�f���istage�ɋA���j - �s��
            size_t IdxSign_{};
            // ���葤�̏o���ʒu - �s��
            Direction dirPartner_{};
        };

        struct Info_t
        {
            Vector3* topLeftPosPtr_{};
            // �v�Z�ʗ}���I�t�Z�b�g
            Vector2 offset_{};
            Transform transform_{};
            BlockDrawer bd_{};

        public:
            Info_t(Vector3* basePosPtr, const Vector2& offset) : topLeftPosPtr_(basePosPtr), offset_(offset)
            {
                Transform::Status status{ *basePosPtr + Vector3{offset.x_,offset.y_,0},{0,0,0},{1,1,1} };
                transform_.Initialize(status);
            }

            void Initialize(int bt) {
                bd_.Initialize(&transform_, static_cast<IMode::Type>(bt));
            }

            void Update(void) {
                transform_.pos_ = *topLeftPosPtr_ + Vector3{ offset_.x_,offset_.y_,0 };
                transform_.UpdateMatrix();
                bd_.Update();
            }

            void Draw(void) {
                bd_.Draw();
            }
        };

    public:
        // �֐�
        Sign(void) = default;

        void Initialize(const Vector2& mapchipSize);
        void Update(void);
        void Draw(void);

        // �p�[�t�F�N�g�s�N�Z���R���W����
        void PPC(YukiMapchipCollider* ptr);
        const Vector2& CalcVelStuck(const Vector2& pointPos); // �ړ����͂Ȃ��̉����o���l�v�Z�֐� ��Move�̑O�Ɏg�� =>���g���ĂȂ�
        const Vector2& CalcVelMove(const Vector2& pointPos, const Vector2& vel); // �ړ����͂���̉����o���l�v�Z�֐� ��Stuck�̌�Ɏg��

        // �ϐ�
        //std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip2_{};
        std::vector<std::vector<int>> mapchip_{};
        std::list<std::unique_ptr<Info_t>> BDrawerList_{};
        std::map<WarpIdx_t, Vec2Int_t> warpInfos_{};

        // ��_�i����j���W
        Vector3 topLeftPos_{}; // z�͏��0
    };
}

