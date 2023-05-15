#include "StageDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

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
}

void StageDrawer::Initialize(YGame::Transform* pParent, const int number, IMode::Type type)
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
	color_.reset(CBColor::Create());

	// 数字
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		// ビルボード化
		numObjs_[i].reset(Sprite3D::Object::Create({}, true, true, spVP_, color_.get(), nullptr));
		numObjs_[i]->parent_ = &core_->m_;
	}

	// タワー
	towerDra_.Initialize(&core_->m_, type);

	// リセット
	Reset(type);
}

void StageDrawer::Reset(IMode::Type type)
{
	// ----- オブジェクト初期化 ----- //

	// 核
	core_->Initialize({});

	// 数字
	{
		// 位置
		Vector3 pos = Vector3(0.0f, +1.5f, 0.0f);

		numObjs_[0]->Initialize({ pos });

		// 幅
		float x = 0.4f;

		numObjs_[1]->Initialize({ pos + Vector3(+x,0.0f,0.0f) });
		numObjs_[2]->Initialize({ pos + Vector3(-x,0.0f,0.0f) });
	}

	// ビル
	towerDra_.Reset(type);

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

	towerDra_.Update();
}

void StageDrawer::Draw()
{
	// 塔
	towerDra_.Draw(YGame::DrawLocation::Center);

	// 数字
	// 10未満なら
	if (number_ < 10)
	{
		// 1つだけ映す
		spNumberSpr_[number_]->SetDrawCommand(numObjs_[0].get(), YGame::DrawLocation::Center);
	}
	// それ以外なら
	else
	{
		int ones = number_ % 10;
		int tens = number_ / 10;

		spNumberSpr_[ones]->SetDrawCommand(numObjs_[1].get(), YGame::DrawLocation::Center);
		spNumberSpr_[tens]->SetDrawCommand(numObjs_[2].get(), YGame::DrawLocation::Center);
	}
}

