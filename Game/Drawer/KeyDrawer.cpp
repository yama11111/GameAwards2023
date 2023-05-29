#include "KeyDrawer.h"
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

using namespace DrawerConfig::Key;

#pragma endregion

#pragma region Static

array<Model*, KeyDrawerCommon::sPartsNum_> KeyDrawerCommon::spModels_ =
{
	nullptr, nullptr,
};
Ease<float> KeyDrawerCommon::sIdleHeightEase_;

#pragma endregion

#pragma region インデックス

static const size_t BladeIdx = static_cast<size_t>(KeyDrawerCommon::Parts::eBlade); // 刃
static const size_t RingCoreIdx = static_cast<size_t>(KeyDrawerCommon::Parts::eRingCore); // リング核
static const size_t RingShellIdx = static_cast<size_t>(KeyDrawerCommon::Parts::eRingShell); // リング殻

#pragma endregion

#pragma region Common

void KeyDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[BladeIdx] = Model::LoadObj("key/blade", true); // 刃
	spModels_[RingCoreIdx] = Model::LoadObj("key/ring/core", true); // リング核
	spModels_[RingShellIdx] = Model::LoadObj("key/ring/shell", true); // リング殻


	// ----- アニメーション ----- //

	// 立ち高さイージング初期化
	sIdleHeightEase_.Initialize(Idle::Height::Start, Idle::Height::End, Idle::Height::Exponent);
}

#pragma endregion

#pragma region Drawer

void KeyDrawer::Initialize(Transform* pParent)
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

void KeyDrawer::Reset()
{
	// リセット
	IDrawer::Reset();

	// 核の色とマテリアル設定
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[BladeIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BladeIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[RingCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[RingCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[RingShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[RingShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	// オブジェクト初期化(パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}


	// ----- アニメーション ----- //

	// 動く
	isAct_ = true;
	

	// アニメ用初期化
	animeBladePos_ = animeRingPos_ = animeRingRota_ = {};

	
	// 立ちモーションする
	isIdle_ = true;

	// 立ちタイマー初期化
	for (size_t i = 0; i < idlePowers_.size(); i++)
	{
		idlePowers_[i].Initialize(Idle::Frame);
	}

}

void KeyDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});


	// アニメ用初期化
	animeBladePos_ = animeRingPos_ = animeRingRota_ = {};

	// リング位置
	animeRingPos_ = Vector3(0.0f, RingHeight, 0.0f);

	// 立ちモーション更新
	UpdateIdleAnimation();


	// 行列更新 (子)
	modelObjs_[BladeIdx]->UpdateMatrix({ animeBladePos_ });
	modelObjs_[RingCoreIdx]->UpdateMatrix({ animeRingPos_, animeRingRota_ });
	modelObjs_[RingShellIdx]->UpdateMatrix({ animeRingPos_, animeRingRota_ });
}

void KeyDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void KeyDrawer::UpdateIdleAnimation()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// 立ちモーションじゃないなら弾く
	if (isIdle_ == false) { return; }


	for (size_t i = 0; i < sSetNum_; i++)
	{
		// パワー更新
		idlePowers_[i].Update(isIdlePowerSwitches_[i]);

		// 0の時
		if (i == 0)
		{
			// スイッチオンなら
			if (isIdlePowerSwitches_[i])
			{

				// 位置
				animeRingPos_.y_ += sIdleHeightEase_.In(idlePowers_[i].Ratio());
			}
			// スイッチオフなら
			else
			{

				// 位置
				animeRingPos_.y_ += sIdleHeightEase_.Out(idlePowers_[i].Ratio());
			}

		}
		// 1 の時
		else if (i == 1)
		{
			// スイッチオンなら
			if (isIdlePowerSwitches_[i])
			{
				// 位置
				animeBladePos_.y_ += sIdleHeightEase_.In(idlePowers_[i].Ratio());
			}
			// スイッチオフなら
			else
			{
				// 位置
				animeBladePos_.y_ += sIdleHeightEase_.Out(idlePowers_[i].Ratio());
			}
		}

		// スイッチ
		if (idlePowers_[i].IsMax()) { isIdlePowerSwitches_[i] = false; }
		else if (idlePowers_[i].IsZero()) { isIdlePowerSwitches_[i] = true; }
	}
}

#pragma endregion