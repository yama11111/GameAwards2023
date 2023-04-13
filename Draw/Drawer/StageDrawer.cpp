#include "StageDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Sprite3DObject;
using YGame::Sprite3D;
using YGame::Texture;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
//using namespace DrawerConfig::Gate;

#pragma endregion

std::array<YGame::Sprite3D*, 10> StageDrawerCommon::spNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
YGame::Model* StageDrawerCommon::spBuildingModel_ = nullptr;
YGame::ViewProjection* StageDrawerCommon::spVP_ = nullptr;

void StageDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- �X�v���C�g�ǂݍ��� ----- //
	
	// ����
	spNumberSpr_[0] = Sprite3D::Create(Texture::Load("Numbers/0.png"));
	spNumberSpr_[1] = Sprite3D::Create(Texture::Load("Numbers/1.png"));
	spNumberSpr_[2] = Sprite3D::Create(Texture::Load("Numbers/2.png"));
	spNumberSpr_[3] = Sprite3D::Create(Texture::Load("Numbers/3.png"));
	spNumberSpr_[4] = Sprite3D::Create(Texture::Load("Numbers/4.png"));
	spNumberSpr_[5] = Sprite3D::Create(Texture::Load("Numbers/5.png"));
	spNumberSpr_[6] = Sprite3D::Create(Texture::Load("Numbers/6.png"));
	spNumberSpr_[7] = Sprite3D::Create(Texture::Load("Numbers/7.png"));
	spNumberSpr_[8] = Sprite3D::Create(Texture::Load("Numbers/8.png"));
	spNumberSpr_[9] = Sprite3D::Create(Texture::Load("Numbers/9.png"));

	// ----- ���f���ǂݍ��� ----- //

	// �r��
	spBuildingModel_ = Model::Load("building", true);
}

void StageDrawer::Initalize(YGame::Transform* pParent, const int number)
{
	// ����
	// 0�ȉ��Ȃ�e��
	assert(number > 0);
	// ���
	number_ = number;

	// ----- ���� ----- //
	
	// �j
	core_.reset(new Transform());
	core_->parent_ = &pParent->m_;

	// �F
	color_.reset(Color::Create());

	// ����
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		// �r���{�[�h��
		numObjs_[i].reset(Sprite3DObject::Create({}, true, true, spVP_, color_.get()));
		numObjs_[i]->parent_ = &core_->m_;
	}

	// �r��
	buildingObjs_.resize(4);
	for (size_t i = 0; i < buildingObjs_.size(); i++)
	{
		buildingObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		buildingObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void StageDrawer::Reset()
{
	// ----- �I�u�W�F�N�g������ ----- //

	// �j
	core_->Initialize({});

	// ����
	{
		// ����
		float y = 1.0f;

		numObjs_[0]->Initialize({ {0.0f,y,0.0f} });

		// ��
		float x = 0.4f;

		numObjs_[1]->Initialize({ {+x,y,0.0f} });
		numObjs_[2]->Initialize({ {-x,y,0.0f} });
	}

	// �r��
	buildingObjs_[0]->Initialize({});
	buildingObjs_[1]->Initialize({});
	buildingObjs_[2]->Initialize({});
	buildingObjs_[3]->Initialize({});


	// �F������
	color_->SetRGBA({ 1.0f,1.0f,1.0f,1.0f });
}

void StageDrawer::Update()
{
	// �j
	core_->UpdateMatrix();
	
	// ����
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		numObjs_[i]->UpdateMatrix();
	}
	
	// �r��
	for (size_t i = 0; i < buildingObjs_.size(); i++)
	{
		buildingObjs_[i]->UpdateMatrix();
	}
}

void StageDrawer::DrawModel()
{
	// �r��
	for (size_t i = 0; i < buildingObjs_.size(); i++)
	{
		spBuildingModel_->Draw(buildingObjs_[i].get());
	}
}

void StageDrawer::DrawSprite3D()
{
	// ����
	// 10�����Ȃ�
	if (number_ < 10)
	{
		// 1�����f��
		spNumberSpr_[number_]->Draw(numObjs_[0].get());
	}
	// ����ȊO�Ȃ�
	else
	{
		int ones = number_ % 10;
		int tens = number_ / 10;

		spNumberSpr_[ones]->Draw(numObjs_[1].get());
		spNumberSpr_[tens]->Draw(numObjs_[2].get());
	}
}
