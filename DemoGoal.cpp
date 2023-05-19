#include "DemoGoal.h"

using YGame::Transform;
using YMath::Vector3;

void DemoGoal::Initialize(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get());

	// ���Z�b�g
	Reset(pos);
}

void DemoGoal::Reset(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos, {0.0f,+0.4f,0.0f}, {1.0f,1.0f,1.0f} });

	// �ʒu���
	center_ = transform_->pos_;

	// ���a�ݒ�
	SafeSetRadius(1.5f);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void DemoGoal::Update()
{
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �ʒu���
	center_ = transform_->pos_;

	// �`��N���X�X�V
	drawer_.Update();
}

void DemoGoal::Draw()
{
	// �`��
	drawer_.Draw();
}

void DemoGoal::Goal(const YMath::Vector3& playerPos)
{
	// �S�[��
	isGoal_ = true;

	// �S�[�����[�V�����J�n
	drawer_.ActivateClearAnimation(playerPos);
}
