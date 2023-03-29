#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
std::array<std::unique_ptr<Model>, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* PlayerDrawerCommon::spVP_ = nullptr;

void PlayerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// ��
	sModels_[static_cast<size_t>(Parts::Normal)].reset(Model::LoadObj("player/playerNormal", true));
	sModels_[static_cast<size_t>(Parts::Red)]	.reset(Model::LoadObj("player/playerRed", true));
}

#pragma endregion

void PlayerDrawer::Initialize(YMath::Matrix4* pParent, Vector3* pDirection, const Mode& mode)
{
	// null�`�F�b�N
	assert(pDirection);

	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
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
		modelObjs_[i]->Initialize({});
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
		modelObjs_[i]->UpdateMatrix();
	}
}

void PlayerDrawer::Draw()
{
	// �`��
	//for (size_t i = 0; i < sModels_.size(); i++)
	//{
	//	sModels_[i]->Draw(modelObjs_[i].get());
	//}
	
	sModels_[static_cast<size_t>(current_)]->Draw(modelObjs_[static_cast<size_t>(current_)].get());
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
