#include "Skydome.h"
#include <cassert>

void Skydome::Initialize()
{
	// ������
	transform_.Initialize({});
	drawer_.Initialize(&transform_.m_, 200.0f);

	// ���Z�b�g
	Reset();
}

void Skydome::Reset()
{
	transform_.Initialize({});
	drawer_.Reset(200.0f);
}

void Skydome::Update()
{
	// �X�V
	transform_.UpdateMatrix();

	drawer_.Update();
}

void Skydome::Draw()
{
	// �`��
	drawer_.Draw();
}