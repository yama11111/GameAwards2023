#include "PlatformDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

array<Model*, PlatformDrawerCommon::sPartsNum_> PlatformDrawerCommon::spModels_ =
{
	nullptr, nullptr,
};

unique_ptr<CBMaterial> PlatformDrawerCommon::sHologramMate_ = nullptr;

#pragma endregion

#pragma region インデックス

static const size_t HologramIdx = static_cast<size_t>(PlatformDrawerCommon::Parts::eHologram); // ホログラム
static const size_t LeftIdx = static_cast<size_t>(PlatformDrawerCommon::Parts::eLeft); // 左
static const size_t RightIdx = static_cast<size_t>(PlatformDrawerCommon::Parts::eRight); // 右

#pragma endregion

#pragma region Common

void PlatformDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ブロック (黒)
	spModels_[HologramIdx]	 = Model::LoadObj("platform/hologram", true); // ホログラム
	spModels_[LeftIdx]		 = Model::LoadObj("platform/left", true); // 左
	spModels_[RightIdx]		 = Model::LoadObj("platform/right", true); // 右

	// ----- オブジェクト ----- //

	sHologramMate_.reset(CBMaterial::Create());
	sHologramMate_->SetAlpha(0.25f);
}

#pragma endregion

#pragma region Drawer

void PlatformDrawer::Initialize(Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void PlatformDrawer::Reset()
{
	// リセット
	IDrawer::Reset();


	// 核の色とマテリアル設定
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;
		
	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGreen);
	pMaterial = sHologramMate_.get();

	modelObjs_[HologramIdx]->SetColor(pColor);
	modelObjs_[HologramIdx]->SetMaterial(pMaterial);
}

void PlatformDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	modelObjs_[HologramIdx]->UpdateMatrix();

	float pos = 1.0f - (1.6f / pParent_->scale_.x_);
	float sca = pParent_->scale_.y_ / pParent_->scale_.x_;
	
	modelObjs_[LeftIdx]->pos_.x_ = -pos;
	modelObjs_[LeftIdx]->scale_.x_ = sca;
	modelObjs_[LeftIdx]->UpdateMatrix({ {}, {}, {} });

	modelObjs_[RightIdx]->pos_.x_ = +pos;
	modelObjs_[RightIdx]->scale_.x_ = sca;
	modelObjs_[RightIdx]->UpdateMatrix({ {}, {}, {} });
}

void PlatformDrawer::Draw()
{
	// モデルの数描画
	spModels_[LeftIdx]->SetDrawCommand(modelObjs_[LeftIdx].get(), YGame::DrawLocation::Center);
	spModels_[RightIdx]->SetDrawCommand(modelObjs_[RightIdx].get(), YGame::DrawLocation::Center);
	spModels_[HologramIdx]->SetDrawCommand(modelObjs_[HologramIdx].get(), YGame::DrawLocation::Center);
}

#pragma endregion