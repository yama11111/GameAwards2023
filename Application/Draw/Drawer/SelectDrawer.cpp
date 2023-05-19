#include "SelectDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "DrawerConfig.h"
#include "StageConfig.h"
#include "CoreColor.h"
#include <cassert>
#include <cmath>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2D;
using YGame::Model;
using YGame::Texture;
using YGame::CBColor;
using YGame::CBMaterial;
using YGame::CBLightGroup;
using YGame::SlimeActor;
using YGame::LetterBoxDrawer;
using YMath::Vector3;
using YMath::GetRand;
using namespace DrawerConfig::Select;

#pragma endregion

Model* SelectDrawerCommon::spEarthModel_ = nullptr;
Sprite2D* SelectDrawerCommon::spLogoSpr_ = nullptr;
YGame::ViewProjection* SelectDrawerCommon::spVP_ = nullptr;
StageConfig* SelectDrawerCommon::spStageConfig_ = nullptr;
std::unique_ptr<YGame::CBMaterial> SelectDrawerCommon::sTowerMate_;
std::unique_ptr<YGame::CBLightGroup> SelectDrawerCommon::sTowerLight_;
std::unique_ptr<YGame::CBMaterial> SelectDrawerCommon::sEarthMate_;
std::unique_ptr<YGame::CBLightGroup> SelectDrawerCommon::sEarthLight_;
YGame::ParticleManager* SelectDrawerCommon::spParticleMan_ = nullptr;

void SelectDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pParticleMan);
	// ���
	spVP_ = pVP;
	spParticleMan_ = pParticleMan;

	// ----- �X�v���C�g�ǂݍ��� ----- //
	
	// ���S
	spLogoSpr_ = Sprite2D::Create({}, { Texture::Load("Select/logo.png", false) });

	// ----- ���f���ǂݍ��� ----- //

	// �n��
	spEarthModel_ = Model::LoadObj("earth", true);


	// �X�e�[�W�ݒ菊��
	spStageConfig_ = StageConfig::GetInstance();


	// ����
	sTowerMate_.reset(CBMaterial::Create());
	sTowerMate_->SetAmbient(Tower::Material::Ambient);

	sTowerLight_.reset(CBLightGroup::Create());
	sTowerLight_->SetAmbientColor(Tower::Light::Ambient);
	sTowerLight_->SetDirectionalLightActive(0, true);
	sTowerLight_->SetDirectionalLightColor(0, Tower::Light::Direction::Color);
	sTowerLight_->SetDirectionalLightDirection(0, Tower::Light::Direction::Dire);

	sEarthMate_.reset(CBMaterial::Create());
	sEarthMate_->SetAmbient(Earth::Material::Ambient);

	sEarthLight_.reset(CBLightGroup::Create());
	sEarthLight_->SetAmbientColor(Earth::Light::Ambient);
	sEarthLight_->SetDirectionalLightActive(0, true);
	sEarthLight_->SetDirectionalLightColor(0, Earth::Light::Direction::Color);
	sEarthLight_->SetDirectionalLightDirection(0, Earth::Light::Direction::Dire);

	// �j�F
	CoreColor::StaticInitialize(false);

	// �^���[
	TowerDrawerCommon::StaticInitialize(sTowerMate_.get(), sTowerLight_.get());

	// �V��
	SkydomeDrawerCommon::StaticInitialize(CoreColor::ColorPtr(CoreColor::ColorType::eRed));


	// ���^�[�{�b�N�X
	YGame::LetterBoxDrawerCommon::StaticInitialize();

	// �X�e�[�W
	StageDrawerCommon::StaticInitialize(pVP);

	// �J�[�h
	CardDrawerCommon::StaticInitialize();
}

void SelectDrawer::Initialize()
{
	// ----- ���� ----- //

	// �j
	core_.reset(new Transform());

	// �F
	color_.reset(CBColor::Create());

	// �n��
	earthObj_.reset(YGame::Model::Object::Create(
		Transform::Status::Default(), 
		spVP_, 
		color_.get(), 
		sEarthMate_.get(),
		sEarthLight_.get()));

	earthObj_->parent_ = &core_->m_;

	// �X�e�[�W�g�����X�t�H�[�� (�g���p)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i].reset(new Transform());
		aliveStages_[i]->parent_ = &core_->m_;
	}
	
	// �X�e�[�W�g�����X�t�H�[�� (�g��Ȃ��p)
	deadStage_.reset(new Transform());
	
	// �X�e�[�W�`��N���X
	stageDras_.resize(spStageConfig_->StageNum_); // ���T�C�Y
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i].reset(new StageDrawer());

		// �ԍ����g�����X�t�H�[���̐���菬�����Ȃ�
		if (i < aliveStages_.size())
		{
			// �g���p�̃g�����X�t�H�[������
			stageDras_[i]->Initialize(aliveStages_[i].get(), static_cast<int>(i + 1), TowerDrawerCommon::Type::eBlack);
		}
		// ����ȊO�Ȃ�
		else
		{
			// �g��Ȃ��p�̃g�����X�t�H�[������
			stageDras_[i]->Initialize(deadStage_.get(), static_cast<int>(i + 1), TowerDrawerCommon::Type::eBlack);
		}
	}
	

	// �X�e�[�W�J�[�h
	cards_.resize(spStageConfig_->StageNum_);
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].reset(new Transform());
	}

	// �X�e�[�W�J�[�h�`��N���X
	cardDras_.resize(spStageConfig_->StageNum_);
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i].reset(new CardDrawer());
		cardDras_[i]->Initialize(cards_[i].get(), static_cast<int>(i + 1));
	}

	// ���^�[�{�b�N�X������
	lbDra_.reset(new LetterBoxDrawer());
	lbDra_->Initialize(LetterBox::TopHeight, LetterBox::BottomHeight);


	// ���S������
	logoObj_.reset(Sprite2D::Object::Create());


	// �V��
	skydome_.reset(new Transform());
	skydomeDra_.Initialize(&skydome_->m_, 800.0f);

	// ----- �C�[�W���O ----- //

	// �X�e�[�W��]�p�p���[
	int staNum = spStageConfig_->StageNum_ - 1;
	stageRotaPows_.resize(static_cast<size_t>(staNum)); // ���T�C�Y

	// �A�O���b�h�����p�^�C�}�[
	emitBubbleGridTim_.Initialize(BubbleGrid::IntervalFrame);

	// ���Z�b�g
	Reset();
}

void SelectDrawer::Reset()
{
	// ----- �I�u�W�F�N�g������ ----- //
	
	// �j
	core_->Initialize();

	// �傫���̗�
	float earthScaleVal = Earth::Scale;
	// ��]�̗�
	float rotaVal = (PI * 2.0f) / static_cast<float>(aliveStages_.size());

	// �n��
	earthObj_->Initialize({ {},{},{earthScaleVal,earthScaleVal,earthScaleVal} });
	color_->Initialize(Earth::Color);

	// ----- �X�e�[�W ----- //

	// �g�����X�t�H�[�� (�g���p)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		// �ʒu
		float pos = earthScaleVal - 0.5f;

		// ��] ((360 / size) * idx)
		float rota = rotaVal * i;

		// ��]�ʂɍ��킹���ʒu�ɂȂ�悤��
		aliveStages_[i]->Initialize(
			{
				{ 0.0f, +pos * cosf(rota), +pos * sinf(rota) }, // �ʒu
				{ rota, 0, 0 }, // ��]
				{ 1.0f, 1.0f, 1.0f } // �傫��
			}
		);
	}
	// �g�����X�t�H�[�� (�g��Ȃ��p)
	deadStage_->Initialize({ {-2000,-2000,-2000}, {}, {} });
	
	// �`��N���X
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		// ���
		TowerDrawerCommon::Type type = TowerDrawerCommon::Type::eBlack;

		// �N���A���Ă���Ȃ�ύX
		if (spStageConfig_->GetIsClearStage((int)i))
		{
			// �N���A���Ă���Ȃ�ύX
			type = TowerDrawerCommon::Type::eWhite;
		}

		stageDras_[i]->Reset(type);
	}

	// ----- �X�e�[�W�J�[�h ----- //

	// �����̕�
	float heightVal = Card::TotalHeight / static_cast<float>(spStageConfig_->StageNum_ - 1);

	// �g�����X�t�H�[�� (�e)
	for (size_t i = 0; i < cards_.size(); i++)
	{
		// y �̈ʒu
		float y = Card::CenterHeight + (Card::TotalHeight / 2.0f)
			- heightVal * static_cast<float>(i);
		
		cards_[i]->Initialize(
			{
				{ Card::DefPosX, y, 0.0f },
				{},
				{ 1.0f, 1.0f, 1.0f }
			}
		);
	}
	// �`��N���X
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		// �N���A���Ă���Ȃ�ύX
		cardDras_[i]->Reset(spStageConfig_->GetIsClearStage((int)i));
	}


	// ���^�[�{�b�N�X
	lbDra_->Reset();


	// ���S
	logoObj_->Initialize({ Logo::Pos, {}, {1.0f,1.0f,0.0f} });

	// �V��
	skydomeDra_.Reset(800.0f);

	// ----- ���̑������� ----- //

	// ���쒆��
	isAct_ = false;

	// �J�n����]�p�C�[�W���O
	startRotaEas_.Initialize(0.0f, -rotaVal / 2.0f, Stage::Exponent);
	
	// �J�n����]�p�^�C�}�[
	startRotaTim_.Initialize(20);
	startRotaTim_.SetActive(true);


	// �X�e�[�W��]�p�C�[�W���O
	stageRotaEas_.Initialize(0.0f, -rotaVal, Stage::Exponent);

	// �X�e�[�W��]�p�p���[
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		stageRotaPows_[i].Initialize(Stage::Frame);
	}

	// �A�O���b�h�����p�^�C�}�[
	emitBubbleGridTim_.Reset(true);

	// �A�O���b�h����
	EmitBubbleCharacter();
}

void SelectDrawer::UpdateRotaAnimation()
{
	// ��]��
	float rotaVal = 0.0f;

	// �J�n����]�^�C�}�[�X�V
	startRotaTim_.Update();
	// �J�n����]����
	rotaVal += startRotaEas_.In(startRotaTim_.Ratio());

	// �X�e�[�W������]������
	// ��]�����̕��X�^�[�g
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		//��]�����邩
		bool isRotaAct = false;
		
		// ���݂̃X�e�[�W�����ԍ����������Ȃ�
		int staIdx = spStageConfig_->GetCurrentStageIndex() - 1;
		if (i < static_cast<size_t>(staIdx))
		{
			// ���삷��
			isRotaAct = true;
		}

		// �X�V
		stageRotaPows_[i].Update(isRotaAct);

		// ��]������Ȃ�C�[�Y�C��
		if (isRotaAct) { rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio()); }
		// ����ȊO�Ȃ�C�[�Y�A�E�g
		else { rotaVal += stageRotaEas_.Out(stageRotaPows_[i].Ratio()); }

		//rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio());
	}

	// �j�ɑ�� (��])
	core_->rota_.x_ = rotaVal;
}

void SelectDrawer::Update()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �A�j���[�V�����̉�]�X�V
	UpdateRotaAnimation();

	// �j
	core_->UpdateMatrix();

	// �n��
	earthObj_->UpdateMatrix();

	// ----- �X�e�[�W ----- //
	
	// �g�����X�t�H�[��
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i]->UpdateMatrix();
	}
	// �`��N���X
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Update();
	}

	// ----- �X�e�[�W�J�[�h ----- //

	// �g�����X�t�H�[��
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i]->UpdateMatrix();
	}
	// �`��N���X
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i]->Update();
		
		// �I�𒆂�
		bool isSelect = false;

		// �I�𒆂̃X�e�[�W�ԍ��̂Ƃ�
		int staIdx = spStageConfig_->GetCurrentStageIndex() - 1;
		if (i == staIdx)
		{
			// �I��
			isSelect = true;
		}

		// �I�𒆂��ݒ�
		cardDras_[i]->SetSelect(isSelect);
	}


	// ���^�[�{�b�N�X
	lbDra_->Update();

	// �V��
	skydomeDra_.Update();

	// �G�~�b�^�[�X�V
	UpdateEmitter();
}

void SelectDrawer::UpdateEmitter()
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

void SelectDrawer::EmitBubbleCharacter()
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


void SelectDrawer::Draw()
{
	// �V��
	skydomeDra_.Draw();

	// �X�e�[�W�`��
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Draw();
	}

	// �n��
	spEarthModel_->SetDrawCommand(earthObj_.get(), YGame::DrawLocation::Center);
	
	// ���^�[�{�b�N�X�`��
	lbDra_->Draw(YGame::DrawLocation::Front);

	// �J�[�h�`�� (��납��)
	for (int i = static_cast<int>(cardDras_.size()) - 1; i >= 0; i--)
	{
		cardDras_[i]->Draw();
	}

	// ���S�`��
	spLogoSpr_->SetDrawCommand(logoObj_.get(), YGame::DrawLocation::Front);
}