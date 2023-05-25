#include "TowerDrawer.h"
#include "CalcTransform.h"
#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;
using YGame::CBLightGroup;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Tower;

#pragma endregion

#pragma region Static

array<array<Model*, TowerDrawerCommon::sPartsNum_>, TowerDrawerCommon::sTypeNum_> TowerDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr,
};
CBMaterial* TowerDrawerCommon::spUniqueMate_ = nullptr;
CBLightGroup* TowerDrawerCommon::spUniqueLight_ = nullptr;

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(TowerDrawerCommon::Parts::eCore); // 核
static const size_t ShellIdx = static_cast<size_t>(TowerDrawerCommon::Parts::eShell); // 殻

static const size_t BlackIdx = static_cast<size_t>(TowerDrawerCommon::Type::eBlack); // 黒
static const size_t WhiteIdx = static_cast<size_t>(TowerDrawerCommon::Type::eWhite); // 白

#pragma endregion

#pragma region Common

void TowerDrawerCommon::StaticInitialize(
	YGame::CBMaterial* pMate,
	YGame::CBLightGroup* pLight)
{
	// nullチェック
	assert(pMate);
	assert(pLight);
	// 代入
	spUniqueMate_ = pMate;
	spUniqueLight_ = pLight;

	// ----- モデル読み込み ----- //

	// 通常
	spModels_[BlackIdx][CoreIdx] = Model::LoadObj("tower/black/core", true); // 核
	spModels_[BlackIdx][ShellIdx] = Model::LoadObj("tower/black/shell", true); // 殻

	// 赤
	spModels_[WhiteIdx][CoreIdx] = Model::LoadObj("tower/white/core", true); // 核
	spModels_[WhiteIdx][ShellIdx] = Model::LoadObj("tower/white/shell", true); // 殻
}

#pragma endregion

#pragma region Drawer

void TowerDrawer::Initialize(Transform* pParent, const Type& type)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		CBMaterial* pMate = nullptr;

		if (i == CoreIdx) { pMate = CoreColor::MaterialPtr(); }
		else if (i == ShellIdx) { pMate = spUniqueMate_; }

		// 生成
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, nullptr, pMate, spUniqueLight_));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset(type);
}

void TowerDrawer::Reset(const Type& type)
{
	// リセット
	IDrawer::Reset();

	// 代入
	type_ = type;

	// インデックスを計算
	typeIndex_ = static_cast<size_t>(type);

	// 核の色とマテリアル設定
	CBColor* pColor = nullptr;

	if (type == Type::eBlack)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGray);
	}
	else if (type == Type::eWhite)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
	}

	modelObjs_[CoreIdx]->SetColor(pColor);

	// オブジェクト初期化(パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}
}

void TowerDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void TowerDrawer::Draw(const YGame::DrawLocation& location)
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[i].get(), location);
	}
}

#pragma endregion