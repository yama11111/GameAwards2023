#include "SkydomeDrawer.h"

using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

std::unique_ptr<Model> SkydomeDrawerCommon::sModel_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize()
{
	// ���f���ǂݍ���
	sModel_.reset(Model::LoadObj("skydome", true));
}

void SkydomeDrawer::Initalize(YMath::Matrix4* pParent)
{
	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g����
	obj_.reset(ModelObject::Create({}, nullptr, color_.get(), nullptr));
	
	// �e�s����
	obj_->parent_ = pParent;

	// ���Z�b�g
	Reset();
}

void SkydomeDrawer::Reset()
{
	// �I�u�W�F�N�g������
	obj_->Initialize(
		{
			{},
			{},
			{ 100.0f, 100.0f, 100.0f }
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
	sModel_->Draw(obj_.get());
}
