#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::IlluminationGridBlock;
using YGame::PlaceGridBlock;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* IlluminationGridBlock::spModel_ = nullptr;
Model* PlaceGridBlock::spModel_ = nullptr;

#pragma region IParticle


void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;
}

void IParticle::Initialize(const uint32_t aliveTime)
{
	// �����t���O
	isAlive_ = true;

	// �����^�C�}�[������ + �J�n
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	// ����
	color_.reset(Color::Create());
	obj_.reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
}

bool IParticle::UpdateLife()
{
	// ����ł���Ȃ�e��
	if (isAlive_ == false) { return false; }

	// �����^�C�}�[�X�V
	aliveTim_.Update();
	// �����^�C�}�[�I�� �� ���S
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	// �����Ă��邩�Ԃ�
	return isAlive_;
}

#pragma endregion


#pragma region IlluminationGridBlock

void IlluminationGridBlock::Emit(
	const uint32_t aliveTime,
	YMath::Matrix4* pParent,
	const YMath::Vector3& color,
	const YMath::Ease<float> alphaEas)
{
	// ---------- Object ---------- //
	
	// ���N���X������
	IParticle::Initialize(aliveTime);

	// �e�s����
	obj_->parent_ = pParent;

	// �����傫��
	obj_->scale_ += Vector3(+0.05f, +0.05f, +0.05f);

	// �F������
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// �A���t�@�l�p�p���[
	alphaPow_.Initialize(aliveTime / 2);

	// �A���t�@�l�p���[�𓮂���
	isActAlphaPower_ = true;

	// �A���t�@�l�C�[�W���O���
	alphaEas_ = alphaEas;
}

void IlluminationGridBlock::Update()
{
	// �����X�V
	if (IParticle::UpdateLife() == false) { return; }

	// Object�X�V
	obj_->UpdateMatrix();


	// �A���t�@�l�p�p���[�X�V
	alphaPow_.Update(isActAlphaPower_);
	
	// �A���t�@�l�p�p���[���ő�Ȃ�
	if (alphaPow_.IsMax())
	{
		// �X�V���~�߂�
		isActAlphaPower_ = false;
	}

	// �A���t�@�l�p���[�𓮂����Ȃ�
	if (isActAlphaPower_)
	{
		// �A���t�@�l�X�V (�C�[�Y�A�E�g)
		color_->SetAlpha(alphaEas_.Out(alphaPow_.Ratio()));
	}
	// ����ȊO�Ȃ�
	else
	{
		// �A���t�@�l�X�V (�C�[�Y�C��)
		color_->SetAlpha(alphaEas_.In(alphaPow_.Ratio()));
	}
}

void IlluminationGridBlock::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}

void IlluminationGridBlock::StaticInitialize(Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

#pragma endregion


#pragma region PlaceGridBlock

void PlaceGridBlock::Emit(
	const uint32_t aliveTime, 
	YMath::Matrix4* pParent, 
	const YMath::Ease<float> scaleEas, 
	const YMath::Vector3& color)
{
	// ---------- Object ---------- //

	// ���N���X������
	IParticle::Initialize(aliveTime);

	// �e�s����
	obj_->parent_ = pParent;

	// �F������
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// �傫���C�[�W���O
	scaleEas_ = scaleEas;

}

void PlaceGridBlock::Update()
{
	// �����X�V
	if (IParticle::UpdateLife() == false) { return; }

	// �傫���C�[�W���O
	float sca = scaleEas_.Out(aliveTim_.Ratio());
	
	// ���
	obj_->scale_ = { sca, sca, sca };

	// Object�X�V
	obj_->UpdateMatrix();
}

void PlaceGridBlock::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}

void PlaceGridBlock::StaticInitialize(Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

#pragma endregion


