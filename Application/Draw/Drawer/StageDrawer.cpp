#include "StageDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Model;
using YGame::Sprite3D;
using YGame::Texture;
using YGame::CBColor;
using YGame::SlimeActor;
using YMath::Vector3;
//using namespace DrawerConfig::Gate;

#pragma endregion

std::array<YGame::Sprite3D*, 10> StageDrawerCommon::spNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
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
}

void StageDrawer::Initialize(YGame::Transform* pParent, const int number, IMode::Type type)
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
	color_.reset(CBColor::Create());

	// ����
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		// �r���{�[�h��
		numObjs_[i].reset(Sprite3D::Object::Create({}, true, true, spVP_, color_.get(), nullptr));
		numObjs_[i]->parent_ = &core_->m_;
	}

	// �^���[
	towerDra_.Initialize(&core_->m_, type);

	// ���Z�b�g
	Reset(type);
}

void StageDrawer::Reset(IMode::Type type)
{
	// ----- �I�u�W�F�N�g������ ----- //

	// �j
	core_->Initialize({});

	// ����
	{
		// �ʒu
		Vector3 pos = Vector3(0.0f, +1.5f, 0.0f);

		numObjs_[0]->Initialize({ pos });

		// ��
		float x = 0.4f;

		numObjs_[1]->Initialize({ pos + Vector3(+x,0.0f,0.0f) });
		numObjs_[2]->Initialize({ pos + Vector3(-x,0.0f,0.0f) });
	}

	// �r��
	towerDra_.Reset(type);

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

	towerDra_.Update();
}

void StageDrawer::Draw()
{
	// ��
	towerDra_.Draw(YGame::DrawLocation::Center);

	// ����
	// 10�����Ȃ�
	if (number_ < 10)
	{
		// 1�����f��
		spNumberSpr_[number_]->SetDrawCommand(numObjs_[0].get(), YGame::DrawLocation::Center);
	}
	// ����ȊO�Ȃ�
	else
	{
		int ones = number_ % 10;
		int tens = number_ / 10;

		spNumberSpr_[ones]->SetDrawCommand(numObjs_[1].get(), YGame::DrawLocation::Center);
		spNumberSpr_[tens]->SetDrawCommand(numObjs_[2].get(), YGame::DrawLocation::Center);
	}
}

