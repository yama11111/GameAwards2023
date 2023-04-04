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
using YMath::Vector3;
using namespace DrawerConfig::Select;

#pragma endregion

std::array<std::unique_ptr<YGame::Sprite2D>, 10> SelectDrawerCommon::sNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
std::unique_ptr<YGame::Model> SelectDrawerCommon::sEarthModel_ = nullptr;
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

	// ����
	sNumberSpr_[0].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/0.png", false) }));
	sNumberSpr_[1].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/1.png", false) }));
	sNumberSpr_[2].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/2.png", false) }));
	sNumberSpr_[3].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/3.png", false) }));
	sNumberSpr_[4].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/4.png", false) }));
	sNumberSpr_[5].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/5.png", false) }));
	sNumberSpr_[6].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/6.png", false) }));
	sNumberSpr_[7].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/7.png", false) }));
	sNumberSpr_[8].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/8.png", false) }));
	sNumberSpr_[9].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/9.png", false) }));

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
	}

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

	// �X�e�[�W�g�����X�t�H�[�� (�g���p)
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

	// �X�e�[�W�g�����X�t�H�[�� (�g��Ȃ��p)
	deadStage_->Initialize({ {-2000,-2000,-2000}, {}, {} });

	// �X�e�[�W�`��N���X
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
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

		stageDras_[i]->Reset();
	}

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

	// �X�e�[�W�I�u�W�F�N�g
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i]->UpdateMatrix();
	}

	// �X�e�[�W�`��N���X
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Update();
	}
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

}
