#include "BackgroundDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
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
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

using namespace DrawerConfig::Background;

#pragma endregion

YGame::ParticleManager* BackgroundDrawerCommon::spParticleMan_ = nullptr;

void BackgroundDrawerCommon::StaticInitialize(YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pParticleMan);
	
	// ���
	spParticleMan_ = pParticleMan;
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
		TowerDrawerCommon::Mode mode = static_cast<TowerDrawerCommon::Mode>(Towers::ModeIdx[i]);

		// �`��N���X������
		newTower->drawer_.Initialize(&newTower->transform_.m_, mode);

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
