#include "SkydomeDrawer.h"

using YGame::Model;
using YGame::CBColor;

Model* SkydomeDrawerCommon::spModel_ = nullptr;
CBColor* SkydomeDrawerCommon::spColor_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize(YGame::CBColor* pColor)
{
	// ���f���ǂݍ���
	spModel_ = Model::LoadObj("skydome", true);

	// �F�|�C���^
	spColor_ = pColor;
}

void SkydomeDrawer::Initialize(YMath::Matrix4* pParent, const float scaleSize)
{
	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create({}, nullptr, spColor_, nullptr, nullptr, nullptr));
	
	// �e�s����
	obj_->parent_ = pParent;

	// ���Z�b�g
	Reset(scaleSize);
}

void SkydomeDrawer::Reset(const float scaleSize)
{
	// �I�u�W�F�N�g������
	obj_->Initialize(
		{
			{},
			{},
			{ scaleSize, scaleSize, scaleSize }
		}
	);
}

void SkydomeDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	// �`��
	spModel_->SetDrawCommand(obj_.get(), YGame::DrawLocation::Back);
}
