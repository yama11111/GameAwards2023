#include "SkydomeDrawer.h"

using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

Model* SkydomeDrawerCommon::spModel_ = nullptr;
Color* SkydomeDrawerCommon::spColor_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize(YGame::Color* pColor)
{
	// ���f���ǂݍ���
	spModel_ = Model::Load("skydome", true);

	// �F�|�C���^
	spColor_ = pColor;
}

void SkydomeDrawer::Initialize(YMath::Matrix4* pParent, const float scaleSize)
{
	// �I�u�W�F�N�g����
	obj_.reset(ModelObject::Create({}, nullptr, spColor_, nullptr, nullptr));
	
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
	spModel_->Draw(obj_.get());
}
