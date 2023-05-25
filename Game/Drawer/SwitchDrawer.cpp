#include "SwitchDrawer.h"
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

using namespace DrawerConfig::Switch;

#pragma endregion

#pragma region Static

array<Model*, SwitchDrawerCommon::sPartsNum_> SwitchDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};
Ease<float> SwitchDrawerCommon::sSwitchOnRotaSpeedEase_;

#pragma endregion

#pragma region インデックス

static const size_t BaseOnCoreIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOnCore); // 台座オン核
static const size_t BaseOnShellIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOnShell); // 台座オン殻
static const size_t BaseOffCoreIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOffCore); // 台座オフ核
static const size_t BaseOffShellIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOffShell); // 台座オフ殻
static const size_t LeverCoreIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eLeverCore); // レバー核
static const size_t LeverShellIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eLeverShell); // レバー殻

static const size_t BlueIdx = static_cast<size_t>(SwitchDrawerCommon::Type::eBlue); // 緑

#pragma endregion

#pragma region Common

void SwitchDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[BaseOnCoreIdx]	 = Model::LoadObj("switch/base/on/core", true); // 台座オン核
	spModels_[BaseOnShellIdx]	 = Model::LoadObj("switch/base/on/shell", true); // 台座オン殻
	spModels_[BaseOffCoreIdx]	 = Model::LoadObj("switch/base/off/core", true); // 台座オフ核
	spModels_[BaseOffShellIdx]	 = Model::LoadObj("switch/base/off/shell", true); // 台座オフ殻
	spModels_[LeverCoreIdx]		 = Model::LoadObj("switch/lever/core", true); // レバー核
	spModels_[LeverShellIdx]	 = Model::LoadObj("switch/lever/shell", true); // レバー殻

	// ----- アニメーション ----- //

	// スイッチオン回転スピードイージング
	sSwitchOnRotaSpeedEase_.Initialize(RotaSpeed::Start, RotaSpeed::End, RotaSpeed::Exponent);
}

#pragma endregion

#pragma region Drawer

void SwitchDrawer::Initialize(Transform* pParent, const Type& type)
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
	Reset(type);
}

void SwitchDrawer::Reset(const Type& type)
{
	// リセット
	IDrawer::Reset();

	// 代入
	type_ = type;

	// インデックスを計算
	typeIndex_ = static_cast<size_t>(type);

	// 核の色とマテリアル設定
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
	pMaterial = CoreColor::MaterialPtr();

	modelObjs_[BaseOnCoreIdx]->SetColor(pColor);
	modelObjs_[BaseOnCoreIdx]->SetMaterial(pMaterial);
	modelObjs_[BaseOffCoreIdx]->SetColor(pColor);
	modelObjs_[BaseOffCoreIdx]->SetMaterial(pMaterial);
	modelObjs_[LeverCoreIdx]->SetColor(pColor);
	modelObjs_[LeverCoreIdx]->SetMaterial(pMaterial);

	// オブジェクト初期化(パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}


	// ----- アニメーション ----- //

	// 動く
	isAct_ = true;

	// アニメ用初期化
	animeBasePos_ = {};
	animeLeverPos_= animeLeverRota_ = {};


	// スイッチオンか
	isSwitchOn_ = false;

	// スイッチオンパワー
	switchOnPower_.Initialize(RotaSpeed::Frame);
}

void SwitchDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});


	// アニメ用初期化
	animeBasePos_ = {};
	animeLeverPos_ = animeLeverRota_ = {};

	animeBasePos_ = Vector3(0.0f, BaseHeight, 0.0f);
	animeLeverPos_ = Vector3(0.0f, LeverHeight, 0.0f);


	// スイッチアニメーション
	UpdateSwitchAnimation();


	// 行列更新 (子)
	modelObjs_[BaseOnCoreIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[BaseOnShellIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[BaseOffCoreIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[BaseOffShellIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[LeverCoreIdx]->UpdateMatrix({ animeLeverPos_, animeLeverRota_ });
	modelObjs_[LeverShellIdx]->UpdateMatrix({ animeLeverPos_, animeLeverRota_ });
}

void SwitchDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void SwitchDrawer::AnimateSwitch(const bool isSwitchOn)
{
	// 代入
	isSwitchOn_ = isSwitchOn;
}

void SwitchDrawer::UpdateSwitchAnimation()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }


	// スイッチオンパワー更新
	switchOnPower_.Update(isSwitchOn_);


	// スイッチオンなら
	if (isSwitchOn_)
	{
		// イーズイン
		animeLeverRota_.z_ += sSwitchOnRotaSpeedEase_.In(switchOnPower_.Ratio());
	}
	// それ以外なら
	else 
	{
		// イーズアウト
		animeLeverRota_.z_ += sSwitchOnRotaSpeedEase_.Out(switchOnPower_.Ratio());
	}


	// 色変更
	CBColor* pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGray);

	if (switchOnPower_.IsMax())
	{
		if (type_ == Type::eBlue)
		{
			pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
		}
	}

	modelObjs_[BaseOnCoreIdx]->SetColor(pColor);
	modelObjs_[BaseOffCoreIdx]->SetColor(pColor);
	modelObjs_[LeverCoreIdx]->SetColor(pColor);
}

#pragma endregion