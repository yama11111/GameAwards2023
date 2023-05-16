#include "BackgroundDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;
using YGame::CBLightGroup;

using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

using namespace DrawerConfig::Background;

#pragma endregion

#pragma region Static

YGame::ParticleManager* BackgroundDrawerCommon::spParticleMan_ = nullptr;
unique_ptr<CBMaterial> BackgroundDrawerCommon::sBackMate_;
unique_ptr<CBLightGroup> BackgroundDrawerCommon::sBackLight_;
bool BackgroundDrawerCommon::sIsUnify_ = false;
Timer BackgroundDrawerCommon::sUnifyTim_;
Ease<Vector3> BackgroundDrawerCommon::sUnifyAmbientEas_;
Ease<Vector3> BackgroundDrawerCommon::sUnifyLightColorEas_;

#pragma endregion

void BackgroundDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pParticleMan);
	
	// ���
	spParticleMan_ = pParticleMan;


	// ����
	sBackMate_.reset(CBMaterial::Create());
	sBackMate_->SetAmbient(Ambient);

	sBackLight_.reset(CBLightGroup::Create());
	sBackLight_->SetAmbientColor(Light::Ambient);
	sBackLight_->SetDirectionalLightActive(0, true);
	sBackLight_->SetDirectionalLightColor(0, Light::Direction::Color);
	sBackLight_->SetDirectionalLightDirection(0, Light::Direction::Dire);

	// �N���A���A���r�G���g�p�^�C�}�[
	sUnifyTim_.Initialize(Unify::Frame);

	// �N���A���w�i�A���r�G���g�C�[�W���O
	sUnifyAmbientEas_.Initialize(Ambient, ClearAmbient, Unify::Exponent);
	
	// �N���A���w�i���C�g�F�C�[�W���O
	sUnifyLightColorEas_.Initialize(Light::Direction::Color, Light::Direction::ClearColor, Unify::Exponent);

	// �^���[
	TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get(), sBackLight_.get());

	// �V��
	SkydomeDrawerCommon::StaticInitialize(CoreColor::ColorPtr(CoreColor::ColorType::Red));
}

void BackgroundDrawerCommon::StaticReset()
{
	// ����t���O
	sIsUnify_ = false;

	// �N���A���A���r�G���g�p�^�C�}�[
	sUnifyTim_.Reset(false);
}

void BackgroundDrawerCommon::StaticUpdate()
{
	// �N���A���A���r�G���g�p�^�C�}�[
	sUnifyTim_.Update();

	// �C�[�Y�C��
	Vector3 ambient = sUnifyAmbientEas_.In(sUnifyTim_.Ratio());

	// �A���r�G���g�ݒ�
	sBackMate_->SetAmbient(ambient);

	// �C�[�Y�C��
	Vector3 color = sUnifyLightColorEas_.In(sUnifyTim_.Ratio());

	// ���C�g�F�ݒ�
	sBackLight_->SetDirectionalLightColor(0, color);
}

void BackgroundDrawerCommon::StaticUnify()
{
	// ����J�n
	sIsUnify_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	sUnifyTim_.Reset(true);
}

void BackgroundDrawer::Initialize()
{
	// �V��
	skydome_.Initialize({});
	
	// �V���`��N���X
	skydomeDra_.Initialize(&skydome_.m_, SkydomeSize);


	// �A�O���b�h�����p�^�C�}�[
	emitBubbleGridTim_.Initialize(BubbleGrid::IntervalFrame);


	// ���Z�b�g
	Reset();
}

void BackgroundDrawer::Reset()
{
	// �^���[������
	InitializeTowers();

	// �V��
	skydome_.Initialize({});

	// �V���`��N���X
	skydomeDra_.Reset(SkydomeSize);


	// �A�O���b�h�����p�^�C�}�[
	emitBubbleGridTim_.Reset(true);

	// �A�O���b�h����
	EmitBubbleCharacter();
}

void BackgroundDrawer::Update()
{
	// �^���[����
	for (std::unique_ptr<Tower>& tower : towers_)
	{
		//// �e�g�����X�t�H�[���X�V
		//tower->transform_.UpdateMatrix();

		// �`��N���X�X�V
		tower->drawer_.Update();
	}

	// �V��
	skydome_.UpdateMatrix();

	// �V���`��N���X
	skydomeDra_.Update();

	// �G�~�b�^�[�X�V
	UpdateEmitter();
}

void BackgroundDrawer::Draw()
{
	// �V��
	skydomeDra_.Draw();

	// �^���[����
	for (std::unique_ptr<Tower>& tower : towers_)
	{
		// �`��
		tower->drawer_.Draw(YGame::DrawLocation::Center);
	}
}

void BackgroundDrawer::InitializeTowers()
{
	// �^���[���X�g���󂶂�Ȃ��Ȃ�
	if (towers_.empty() == false)
	{
		// ���X�g�N���A
		towers_.clear();
	}

	// ����̐�����
	for (size_t i = 0; i < Towers::Num; i++)
	{
		// �V�K�^���[����
		std::unique_ptr<Tower> newTower = std::make_unique<Tower>();

		// �e�g�����X�t�H�[��������
		newTower->transform_.Initialize(
			{
				Towers::Poss[i], Towers::Rotas[i], Towers::Scales[i]
			});

		// ���
		IMode::Type type = static_cast<IMode::Type>(Towers::ModeIdx[i]);

		// �`��N���X������
		newTower->drawer_.Initialize(&newTower->transform_.m_, type);

		// �}��
		towers_.push_back(std::move(newTower));
	}
}

void BackgroundDrawer::UpdateEmitter()
{
	// �����^�C�}�[�X�V
	emitBubbleGridTim_.Update();

	// �^�C�}�[�I����
	if (emitBubbleGridTim_.IsEnd())
	{
		// �A�O���b�h����
		EmitBubbleCharacter();

		// �^�C�}�[���Z�b�g + �J�n
		emitBubbleGridTim_.Reset(true);
	}
}

void BackgroundDrawer::EmitBubbleCharacter()
{
	// �����_���Ȑ�����
	size_t emitNum = GetRand(BubbleGrid::MinNum, BubbleGrid::MaxNum);

	// �p�[�e�B�N������
	spParticleMan_->EmitBubbleCharacter(
		emitNum,
		BubbleGrid::AliveFrame,
		BubbleGrid::Center, BubbleGrid::Range,
		BubbleGrid::MinScaleSize, BubbleGrid::MaxScaleSize,
		BubbleGrid::MinMoveSpeed, BubbleGrid::MaxMoveSpeed,
		BubbleGrid::MinRotaSpeed, BubbleGrid::MaxRotaSpeed,
		BubbleGrid::Color, BubbleGrid::Place,
		YGame::DrawLocation::Back);

}
