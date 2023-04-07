#include "SelectDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "StageConfig.h"
#include <cassert>
#include <cmath>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YGame::ModelObject;
using YGame::Model;
using YGame::TextureManager;
using YGame::Color;
using YGame::SlimeActor;
using YGame::LetterBoxDrawer;
using YMath::Vector3;
using namespace DrawerConfig::Select;

#pragma endregion

unique_ptr<Model> SelectDrawerCommon::sEarthModel_ = nullptr;
unique_ptr<Sprite2D> SelectDrawerCommon::sLogoSpr_ = nullptr;
YGame::ViewProjection* SelectDrawerCommon::spVP_ = nullptr;

void SelectDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// �e�N�X�`���}�l�[�W���[�擾
	TextureManager* pTexMan = TextureManager::GetInstance();

	// ----- �X�v���C�g�ǂݍ��� ----- //
	
	// ���S
	sLogoSpr_.reset(Sprite2D::Create({}, { pTexMan->Load("Select/logo.png", false) }));

	// ----- ���f���ǂݍ��� ----- //

	// �n��
	sEarthModel_.reset(Model::LoadObj("earth", true));
}

void SelectDrawer::Initalize(int* pStageIdx)
{
	// null�`�F�b�N
	assert(pStageIdx);
	// ���
	pStageIdx_ = pStageIdx;

	// ----- ���� ----- //

	// �j
	core_.reset(new Transform());

	// �F
	color_.reset(Color::Create());

	// �n��
	earthObj_.reset(YGame::ModelObject::Create({}, spVP_, color_.get(), nullptr));
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
	stageDras_.resize(StageNum); // ���T�C�Y
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i].reset(new StageDrawer());

		// �ԍ����g�����X�t�H�[���̐���菬�����Ȃ�
		if (i < aliveStages_.size())
		{
			// �g���p�̃g�����X�t�H�[������
			stageDras_[i]->Initalize(aliveStages_[i].get(), static_cast<int>(i + 1));
		}
		// ����ȊO�Ȃ�
		else
		{
			// �g��Ȃ��p�̃g�����X�t�H�[������
			stageDras_[i]->Initalize(deadStage_.get(), static_cast<int>(i + 1));
		}
	}
	

	// �X�e�[�W�J�[�h
	cards_.resize(StageNum);
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].reset(new Transform());
	}

	// �X�e�[�W�J�[�h�`��N���X
	cardDras_.resize(StageNum);
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i].reset(new CardDrawer());
		cardDras_[i]->Initialize(cards_[i].get(), static_cast<int>(i + 1));
	}

	// ���^�[�{�b�N�X������
	lbDra_.reset(new LetterBoxDrawer());
	lbDra_->Initialize(LetterBox::TopHeight, LetterBox::BottomHeight);


	// ���S������
	logoObj_.reset(Sprite2DObject::Create({}));


	// ----- �C�[�W���O ----- //

	// �X�e�[�W��]�p�p���[
	stageRotaPows_.resize(static_cast<size_t>(StageNum - 1)); // ���T�C�Y

	// ���Z�b�g
	Reset();
}

void SelectDrawer::Reset()
{
	// ----- �I�u�W�F�N�g������ ----- //
	
	// �j
	core_->Initialize({ {},{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f} });

	// �傫���̗�
	float earthScaleVal = Earth::Scale;
	// ��]�̗�
	float rotaVal = (PI * 2.0f) / static_cast<float>(aliveStages_.size());

	// �n��
	earthObj_->Initialize({ {},{},{earthScaleVal,earthScaleVal,earthScaleVal} });
	color_->Initialize({ 0.1f,0.0f,0.1f,1.0f });

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
		stageDras_[i]->Reset();
	}

	// ----- �X�e�[�W�J�[�h ----- //

	// �����̕�
	float heightVal = Card::TotalHeight / static_cast<float>(StageNum - 1);

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
		cardDras_[i]->Reset();
	}


	// ���^�[�{�b�N�X
	lbDra_->Reset();


	// ���S
	logoObj_->Initialize({ Logo::Pos });


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
		if (i < static_cast<size_t>(*pStageIdx_ - 1))
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
		if (i == *pStageIdx_ - 1)
		{
			// �I��
			isSelect = true;
		}

		// �I�𒆂��ݒ�
		cardDras_[i]->SetSelect(isSelect);
	}


	// ���^�[�{�b�N�X
	lbDra_->Update();
}

void SelectDrawer::DrawModel()
{
	// �n��
	sEarthModel_->Draw(earthObj_.get());

	// �X�e�[�W�`��
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->DrawModel();
	}
}
void SelectDrawer::DrawSprite3D()
{
	// �X�e�[�W�`��
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->DrawSprite3D();
	}
}
void SelectDrawer::DrawSprite2D()
{
	// ���^�[�{�b�N�X�`��
	lbDra_->Draw();

	// �J�[�h�`�� (��납��)
	for (int i = static_cast<int>(cardDras_.size()) - 1; i >= 0; i--)
	{
		cardDras_[i]->Draw();
	}

	// ���S�`��
	sLogoSpr_->Draw(logoObj_.get());
}