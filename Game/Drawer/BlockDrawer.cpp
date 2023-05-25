#include "BlockDrawer.h"
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

array<array<Model*, BlockDrawerCommon::sPartsNum_>, BlockDrawerCommon::sTypeNum_> BlockDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
};

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(BlockDrawerCommon::Parts::eCore); // 核
static const size_t ShellIdx = static_cast<size_t>(BlockDrawerCommon::Parts::eShell); // 殻

static const size_t BlackIdx = static_cast<size_t>(BlockDrawerCommon::Type::eBlack); // 黒
static const size_t WhiteIdx = static_cast<size_t>(BlockDrawerCommon::Type::eWhite); // 白

#pragma endregion

#pragma region Common

void BlockDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ブロック (黒)
	spModels_[BlackIdx][CoreIdx] = Model::LoadObj("block/black/core", true); // 核
	spModels_[BlackIdx][ShellIdx] = Model::LoadObj("block/black/shell", true); // 殻

	// ブロック (白)
	spModels_[WhiteIdx][CoreIdx] = Model::LoadObj("block/white/core", true); // 核
	spModels_[WhiteIdx][ShellIdx] = Model::LoadObj("block/white/shell", true); // 殻
}

#pragma endregion

#pragma region Drawer

void BlockDrawer::Initialize(Transform* pParent, const Type& type)
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

void BlockDrawer::Reset(const Type& type)
{
	// リセット
	IDrawer::Reset();

	// 代入
	type_ = type;

	// インデックスを計算
	typeIndex_ = static_cast<size_t>(type);

	// 核の色とマテリアル設定
	CBColor * pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	if (type == Type::eBlack)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGray);
		pMaterial = CoreColor::MaterialPtr();
	}
	else if (type == Type::eWhite)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
		pMaterial = CoreColor::MaterialPtr();
	}

	modelObjs_[CoreIdx]->SetColor(pColor);
	modelObjs_[CoreIdx]->SetMaterial(pMaterial);

	// オブジェクト初期化(パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}
}

void BlockDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

#pragma endregion