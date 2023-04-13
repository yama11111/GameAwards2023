#include "StageDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

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
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- スプライト読み込み ----- //
	
	// 数字
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

	// ----- モデル読み込み ----- //

	// ビル
	spBuildingModel_ = Model::Load("building", true);
}

void StageDrawer::Initalize(YGame::Transform* pParent, const int number)
{
	// 数字
	// 0以下なら弾く
	assert(number > 0);
	// 代入
	number_ = number;

	// ----- 生成 ----- //
	
	// 核
	core_.reset(new Transform());
	core_->parent_ = &pParent->m_;

	// 色
	color_.reset(Color::Create());

	// 数字
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		// ビルボード化
		numObjs_[i].reset(Sprite3DObject::Create({}, true, true, spVP_, color_.get()));
		numObjs_[i]->parent_ = &core_->m_;
	}

	// ビル
	buildingObjs_.resize(4);
	for (size_t i = 0; i < buildingObjs_.size(); i++)
	{
		buildingObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		buildingObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void StageDrawer::Reset()
{
	// ----- オブジェクト初期化 ----- //

	// 核
	core_->Initialize({});

	// 数字
	{
		// 高さ
		float y = 1.0f;

		numObjs_[0]->Initialize({ {0.0f,y,0.0f} });

		// 幅
		float x = 0.4f;

		numObjs_[1]->Initialize({ {+x,y,0.0f} });
		numObjs_[2]->Initialize({ {-x,y,0.0f} });
	}

	// ビル
	buildingObjs_[0]->Initialize({});
	buildingObjs_[1]->Initialize({});
	buildingObjs_[2]->Initialize({});
	buildingObjs_[3]->Initialize({});


	// 色初期化
	color_->SetRGBA({ 1.0f,1.0f,1.0f,1.0f });
}

void StageDrawer::Update()
{
	// 核
	core_->UpdateMatrix();
	
	// 数字
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		numObjs_[i]->UpdateMatrix();
	}
	
	// ビル
	for (size_t i = 0; i < buildingObjs_.size(); i++)
	{
		buildingObjs_[i]->UpdateMatrix();
	}
}

void StageDrawer::DrawModel()
{
	// ビル
	for (size_t i = 0; i < buildingObjs_.size(); i++)
	{
		spBuildingModel_->Draw(buildingObjs_[i].get());
	}
}

void StageDrawer::DrawSprite3D()
{
	// 数字
	// 10未満なら
	if (number_ < 10)
	{
		// 1つだけ映す
		spNumberSpr_[number_]->Draw(numObjs_[0].get());
	}
	// それ以外なら
	else
	{
		int ones = number_ % 10;
		int tens = number_ / 10;

		spNumberSpr_[ones]->Draw(numObjs_[1].get());
		spNumberSpr_[tens]->Draw(numObjs_[2].get());
	}
}
