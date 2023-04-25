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
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::Material;

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
unique_ptr<Material> BackgroundDrawerCommon::sBackMate_;
bool BackgroundDrawerCommon::sIsUnify_ = false;
Timer BackgroundDrawerCommon::sUnifyTim_;
Ease<Vector3> BackgroundDrawerCommon::sUnifyAmbientEas_;

#pragma endregion

void BackgroundDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pParticleMan);
	
	// ���
	spParticleMan_ = pParticleMan;


	// ����
	sBackMate_.reset(YGame::Material::Create(Ambient));


	// �N���A���A���r�G���g�p�^�C�}�[
	sUnifyTim_.Initialize(Unify::Frame);

	// �N���A���w�i�A���r�G���g�C�[�W���O
	sUnifyAmbientEas_.Initialize(Ambient, ClearAmbient, Unify::Exponent);
	

	// �^���[
	TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get());

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
	emitBubbleGridTim_.Initialize(Emit::IntervalFrame);


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
	EmitBubbleGrid();
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
	// �^���[����
	for (std::unique_ptr<Tower>& tower : towers_)
	{
		// �`��
		tower->drawer_.Draw();
	}

	// �V��
	skydomeDra_.Draw();
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
		EmitBubbleGrid();

		// �^�C�}�[���Z�b�g + �J�n
		emitBubbleGridTim_.Reset(true);
	}
}

void BackgroundDrawer::EmitBubbleGrid()
{
	// ������
	size_t emitNum = 0;

	// �����_���Ȑ�����
	emitNum = GetRand(Emit::MinNum, Emit::MaxNum);

	// �����̐�����
	for (size_t i = 0; i < emitNum; i++)
	{

		// �ݒ�p�X�e�[�^�X
		Transform::Status status;

		// �͈͂Ƀ����_���Ȉʒu
		Vector3 range(
			GetRand(-Emit::Range.x_, Emit::Range.x_, Emit::Place),
			GetRand(-Emit::Range.y_, Emit::Range.y_, Emit::Place),
			GetRand(-Emit::Range.z_, Emit::Range.z_, Emit::Place)
		);

		// ���S + �����_���͈͂̈ʒu��
		status.pos_ = Emit::Center + range;

		// �����_���ȃT�C�Y�擾
		float scaleSize =
			GetRand(Emit::MinScaleSize, Emit::MaxScaleSize, Emit::Place);

		// �����_���ȃT�C�Y�K��
		status.scale_ = Vector3(scaleSize, scaleSize, scaleSize);


		// ������Ƀ����_���Ȉړ��X�s�[�h
		Vector3 moveSpeed(
			0.0f,
			GetRand(Emit::MinMoveSpeed, Emit::MaxMoveSpeed, Emit::Place),
			0.0f
		);


		// �S�����Ƀ����_���ȉ�]�X�s�[�h
		Vector3 rotaSpeed(
			GetRand(Emit::MinRotaSpeed, Emit::MaxRotaSpeed, Emit::Place),
			GetRand(Emit::MinRotaSpeed, Emit::MaxRotaSpeed, Emit::Place),
			GetRand(Emit::MinRotaSpeed, Emit::MaxRotaSpeed, Emit::Place)
		);


		// �p�[�e�B�N������
		spParticleMan_->EmitBubbleGrid(
			Emit::AliveFrame,
			status, moveSpeed, rotaSpeed,
			Emit::Color);

	}
}
