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
using YGame::TextureManager;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
//using namespace DrawerConfig::Gate;

#pragma endregion

std::array<std::unique_ptr<YGame::Sprite3D>, 10> StageDrawerCommon::sNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
std::unique_ptr<YGame::Model> StageDrawerCommon::sBuildingModel_ = nullptr;
YGame::ViewProjection* StageDrawerCommon::spVP_ = nullptr;

void StageDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// �e�N�X�`���}�l�[�W���[�擾
	TextureManager* pTexMan = TextureManager::GetInstance();

	// ----- �X�v���C�g�ǂݍ��� ----- //
	
	// ����
	sNumberSpr_[0].reset(Sprite3D::Create(pTexMan->Load("Numbers/0.png")));
	sNumberSpr_[1].reset(Sprite3D::Create(pTexMan->Load("Numbers/1.png")));
	sNumberSpr_[2].reset(Sprite3D::Create(pTexMan->Load("Numbers/2.png")));
	sNumberSpr_[3].reset(Sprite3D::Create(pTexMan->Load("Numbers/3.png")));
	sNumberSpr_[4].reset(Sprite3D::Create(pTexMan->Load("Numbers/4.png")));
	sNumberSpr_[5].reset(Sprite3D::Create(pTexMan->Load("Numbers/5.png")));
	sNumberSpr_[6].reset(Sprite3D::Create(pTexMan->Load("Numbers/6.png")));
	sNumberSpr_[7].reset(Sprite3D::Create(pTexMan->Load("Numbers/7.png")));
	sNumberSpr_[8].reset(Sprite3D::Create(pTexMan->Load("Numbers/8.png")));
	sNumberSpr_[9].reset(Sprite3D::Create(pTexMan->Load("Numbers/9.png")));

	// ----- ���f���ǂݍ��� ----- //

	// �r��
	sBuildingModel_.reset(Model::LoadObj("building", true));
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
		sBuildingModel_->Draw(buildingObjs_[i].get());
	}
}

void StageDrawer::DrawSprite3D()
{
	// ����
	// 10�����Ȃ�
	if (number_ < 10)
	{
		// 1�����f��
		sNumberSpr_[number_]->Draw(numObjs_[0].get());
	}
	// ����ȊO�Ȃ�
	else
	{
		int ones = number_ % 10;
		int tens = number_ / 10;

		sNumberSpr_[ones]->Draw(numObjs_[1].get());
		sNumberSpr_[tens]->Draw(numObjs_[2].get());
	}
}
