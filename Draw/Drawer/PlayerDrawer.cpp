#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;
using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t NormalIdx = 0; // �ʏ�
static const size_t RedIdx = 1; // ��
static const size_t InvisibleIdx = 2; // ����
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // ��


// �ÓI ���f���z�� ������
array<array<unique_ptr<Model>, PlayerDrawerCommon::PartsNum_>, PlayerDrawerCommon::ModeNum_> PlayerDrawerCommon::sModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr,
	nullptr, nullptr
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* PlayerDrawerCommon::spVP_ = nullptr;

void PlayerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// �ʏ�
	sModels_[NormalIdx][BodyIdx].reset(Model::LoadObj("player/playerNormal", true)); // ��
	sModels_[NormalIdx][1].reset(Model::Create());

	// ��
	sModels_[RedIdx][BodyIdx].reset(Model::LoadObj("player/playerRed", true)); // ��
	sModels_[RedIdx][1].reset(Model::Create());

	// ����
	sModels_[InvisibleIdx][BodyIdx].reset(Model::LoadObj("player/playerInvisible", true)); // ��
	sModels_[InvisibleIdx][1].reset(Model::Create());
}

#pragma endregion

void PlayerDrawer::Initialize(YMath::Matrix4* pParent, Vector3* pDirection, const Mode& mode)
{
	// null�`�F�b�N
	assert(pDirection);

	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �����F����
	invisibleColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,0.5f }));

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����ver
			if (i == InvisibleIdx)
			{
				modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, invisibleColor_.get(), nullptr));
			}
			// �ʏ�A��ver
			else
			{
				modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
			}
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	// �����|�C���^�}��
	pDirection_ = pDirection;

	// ���Z�b�g
	Reset(mode);
}

void PlayerDrawer::Reset(const Mode& mode)
{
	// ���Z�b�g
	IDrawer::Reset(mode);

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����ver
			if (i == InvisibleIdx)
			{
				Vector3 scaleVal = { 0.99f,0.99f,0.99f };
				modelObjs_[i][j]->Initialize({ {},{},scaleVal });
			}
			// �ʏ�A��ver
			else
			{
				modelObjs_[i][j]->Initialize({});
			}
		}
	}

	ChangeColorAnimation(mode);
}

void PlayerDrawer::Update()
{
	// �������킹
	Vector3 dire = YMath::AdjustAngle(*pDirection_);

	// ���N���X�X�V 
	IDrawer::Update(
		{
			{}, 
			dire,
			{}
		}
	);

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			modelObjs_[i][j]->UpdateMatrix();
		}
	}
}

void PlayerDrawer::PreDraw()
{
	// �����`��
	sModels_[InvisibleIdx][BodyIdx]->Draw(modelObjs_[InvisibleIdx][BodyIdx].get());

	// �ʏ�Ȃ�
	if (current_ == Mode::Normal)
	{
		// �`��
		sModels_[NormalIdx][BodyIdx]->Draw(modelObjs_[NormalIdx][BodyIdx].get());
	}
}

void PlayerDrawer::PostDraw()
{
	// �ԂȂ�
	if (current_ == Mode::Red)
	{
		// �`��
		sModels_[RedIdx][BodyIdx]->Draw(modelObjs_[RedIdx][BodyIdx].get());
	}
}

void PlayerDrawer::JumpAnimation()
{
	// �L�k��
	Vector3 val = core_->scale_ * DrawerConfig::Player::Jump::SlimeAction::Value;
	val.y_ *= -1.0f;

	// �Ԃ���
	Vector3 squash = +val;
	// �̂т��
	Vector3 streach = -val;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Jump::SlimeAction::Frame;
	// �w�� (�ɋ})
	float pow = DrawerConfig::Player::Jump::SlimeAction::Power;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}

void PlayerDrawer::LandingAnimation()
{
	// �Ԃ���
	Vector3 squash = core_->scale_ * DrawerConfig::Player::Landing::SlimeAction::Value;
	squash.y_ *= -1.0f;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Landing::SlimeAction::Frame;
	// �w�� (�ɋ})
	float exponent = DrawerConfig::Player::Landing::SlimeAction::Power;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}

void PlayerDrawer::ChangeColorAnimation(const Mode& mode)
{
	current_ = mode;
}

void PlayerDrawer::IdleAnimation()
{
}
