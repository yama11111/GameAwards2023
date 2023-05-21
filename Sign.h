#pragma once
#include <map>
#include "Keys.h"
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

        static constexpr float blockRadius_{ 1.f }; // �u���b�N�̔��a

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

        // ������enum
        enum class Direction
        {
            TOP,
            RIGHT,
            LEFT,
            BOTTOM,
        };

        // ���[�v�u���b�N�̏���
        struct WarpIdx_t
        {
        public:
            WarpIdx_t(Direction dirSelf,const std::pair<size_t,size_t>& mces) : dirSelf_(dirSelf),mapchipElemSelf_(mces) {}

            // �������ڑ��ς݂� - ��
            bool isConnected_{};
            // ������"�u���b�N"�̔z��v�f���i�ŔɋA���j - �s��
            std::pair<size_t, size_t> mapchipElemSelf_{};
            // �������̏o������ - �s��
            Direction dirSelf_{};

            // �����"�u���b�N"�̔z��v�f���i�ŔɋA���j - �s��
            std::pair<size_t,size_t> mapchipElemPartner_{};
            // �����"�Ŕ�"�̔z��v�f���istage�ɋA���j - �s��
            size_t IdxSign_{};
            // ���葤�̏o������ - �s��
            Direction dirPartner_{};
        };

        // �u���b�N�S�ʗp���
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

            void Initialize(int bt) { // int 0 = ��C���肾���Aenum �Ƃ����̂őΉ��@�����@-1
                bd_.Initialize(&transform_, static_cast<BlockDrawerCommon::Type>(bt - 1));
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

        void DrawDebug(void);

        // �p�[�t�F�N�g�s�N�Z���R���W����
        void PPC(YukiMapchipCollider* ptr);
        // ��C�u���b�N�𑼃u���b�N�ɒu���ł���B����ȊO�͗�O�X���[
        void ReWriteBlock(size_t X,size_t Y,BlockType bt);
        void ReWriteBlock2Warp(size_t X,size_t Y,BlockType bt, Direction dirSelf);

        inline Vector3 GetCenterPos(void);
    private:
        // (���ݒn + vel) - ��_ �ŋ����Z�o ���v���C���[�͊Ŕ̊�_���K���E�ɂ���z��
        // ���� / �u���b�N�̒��a �Ń}�b�v�`�b�v�z��̗v�f���ł͉��Ԗڂɑ�������ʒu���Z�o ->CalcElem()�ŏ���
        inline int CalcElemX(float pointX) { return static_cast<int>((pointX - topLeftPos_.x_) / (blockRadius_ * 2)); }
        inline int CalcElemY(float pointY) { return static_cast<int>((pointY - topLeftPos_.y_) / (blockRadius_ * 2) * -1); }
        inline int CalcMovedElemX(float pointX, float velX) { return static_cast<int>(std::fabs(pointX + velX - topLeftPos_.x_) / (blockRadius_ * 2)); }
        inline int CalcMovedElemY(float pointY, float velY) { return static_cast<int>(std::fabs(pointY + velY - topLeftPos_.y_) / (blockRadius_ * 2)); }
        float roundToDecimal(float value, int decimalPlaces); // �ۂߌ덷���C������֐�
        bool SlowlyFillingSpaceX(YukiMapchipCollider* ptr, float& pointX, const Vector2& approach, int mElemX, int elemY);
        bool SlowlyFillingSpaceY(YukiMapchipCollider* ptr, float& pointY, const Vector2& approach, int elemX, int mElemY/*, bool gravity*/);
    public:
        // �ϐ�
        //std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip2_{};
        std::vector<std::vector<int>> mapchip_{};
        std::list<std::unique_ptr<Info_t>> BDrawerList_{};
        std::vector<WarpIdx_t> warpInfos_{};

        // ��_�i����j���W
        Vector3 topLeftPos_{}; // z�͏��0

        YInput::Keys* keys_{ YInput::Keys::GetInstance() };
    };
}

