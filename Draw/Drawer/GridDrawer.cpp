#include "GridDrawer.h"
#include "DrawerConfig.h"
#include <cassert>

using YGame::Model;
using YGame::ModelObject;
using YGame::Color;
using YMath::Vector3;
using namespace DrawerConfig::Grid;

YGame::Model* GridDrawerCommon::spGridMod_ = nullptr;
YGame::ViewProjection* GridDrawerCommon::spVP_;

void GridDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);

	// ���
	spVP_ = pVP;

	// �O���b�h���f���ǂݍ���
	spGridMod_ = Model::Load("grid", false);
}

void GridDrawer::Initalize(const YMath::Vector3& leftTop, const YMath::Vector3& num, const float scaleSize)
{
	// �F����
	color_.reset(Color::Create());

	// �N���A
	grids_.clear();

	// �O���b�h�u���b�N�̔z�u
	for (size_t y = 0; y < static_cast<size_t>(num.y_); y++)
	{
		for (size_t x = 0; x < static_cast<size_t>(num.x_); x++)
		{
			for (size_t z = 0; z < static_cast<size_t>(num.z_); z++)
			{
				// �傫��
				Vector3 sca = { scaleSize, scaleSize, scaleSize };

				// �ʒu
				Vector3 pos = { (scaleSize * 4.0f) * x, -(scaleSize * 4.0f) * y, (scaleSize * 4.0f) * z };


				// ���f���p�I�u�W�F�N�g
				std::unique_ptr<ModelObject> newObj;
				newObj.reset(ModelObject::Create({ leftTop + pos, {}, sca }, spVP_, color_.get(), nullptr, nullptr));

				// �����ɑ}��
				grids_.push_back(std::move(newObj));
			}
		}
	}

	// �p���[
	alphaPow_.Initialize(Alpha::Frame);

	// �C�[�W���O
	alphaEas_.Initialize(Alpha::Start, Alpha::End, Alpha::Exponent);


	// ���Z�b�g
	Reset();
}

void GridDrawer::Reset()
{
	// �A���t�@�l�A�j���[�V���������邩
	isActAlpha_ = false;

	// �A���t�@�l�X�C�b�`���[
	isSwitchAlpha_ = false;

	// �p���[
	alphaPow_.Reset();
	
	// �F������
	color_->SetRGB(DefColor);
}

void GridDrawer::ActAlphaAnimation()
{
	// ���Z�b�g
	Reset();

	// �A���t�@�l�A�j���[�V�����J�n
	isActAlpha_ = true;
}

void GridDrawer::UpdateAlphaAnimation()
{
	// �A�j���[�V�������Ȃ��Ȃ�e��
	if (isActAlpha_ == false) { return; }

	// �A���t�@�l�p���[�X�V
	alphaPow_.Update(isSwitchAlpha_);

	// ����p�A���t�@�l
	float alpha = 0.0f;

	// �X�C�b�`�I���Ȃ�
	if (isSwitchAlpha_) 
	{
		// �C�[�Y�C��
		alpha = alphaEas_.Out(alphaPow_.Ratio()); 
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g
		alpha = alphaEas_.In(alphaPow_.Ratio());
	}

	// �A���t�@�l�ݒ�
	color_->SetAlpha(alpha);


	// �A���t�@�l�p���[���ő�Ȃ�
	if (alphaPow_.IsMax())
	{
		// �X�C�b�`�I�t
		isSwitchAlpha_ = false;
	}
	// �A���t�@�l�p���[���[���Ȃ�
	else if (alphaPow_.IsZero())
	{
		// �X�C�b�`�I��
		isSwitchAlpha_ = true;
	}
}

void GridDrawer::Update()
{
	// �A���t�@�l�A�j���[�V�����X�V
	UpdateAlphaAnimation();


	// �O���b�h���X�V
	for (std::unique_ptr<ModelObject>& grid : grids_)
	{
		grid->UpdateMatrix();
	}
}

void GridDrawer::Draw()
{
	// �O���b�h���`��
	for (std::unique_ptr<ModelObject>& grid : grids_)
	{
		spGridMod_->Draw(grid.get());
	}
}
