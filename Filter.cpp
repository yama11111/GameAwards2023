#include "Filter.h"

//�C���N�������g
Filter::Filter()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	filterDra_.Initialize(&filter_);
}

//�f�N�������g
Filter::~Filter()
{
}

//������
void Filter::Initialize()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {2.0f,2.0f,2.0f} });
	filterDra_.Initialize(&filter_);
}

void Filter::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
{
	// �t�B���^�[
	filter_.Initialize({ pos_, rot_, scale_ });
	filterDra_.Initialize(&filter_);
}

//�X�V
void Filter::Update()
{
	//�X�V
	filter_.UpdateMatrix();
	filterDra_.Update();
}

//�`��ق���Post��Pre�̊Ԃɕ`�悷��
void Filter::Draw()
{
	//�`��
	filterDra_.Draw();
}

//���Z�b�g
void Filter::Reset()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {2.0f,2.0f,2.0f} });

	//�K�����Z�b�g���邱��
	filterDra_.Reset();
}
