#include "JunctionDrawer.h"
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

array<array<Model*, JunctionDrawerCommon::sPartsNum_>, JunctionDrawerCommon::sTypeNum_> JunctionDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	//nullptr, nullptr,
};

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(JunctionDrawerCommon::Parts::eCore); // 核
static const size_t ShellIdx = static_cast<size_t>(JunctionDrawerCommon::Parts::eShell); // 殻

static const size_t GreenIdx = static_cast<size_t>(JunctionDrawerCommon::Type::eGreen); // 緑
//static const size_t WhiteIdx = static_cast<size_t>(JunctionDrawerCommon::Type::); // 赤

#pragma endregion

#pragma region Common

void JunctionDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ブロック (黒)
	spModels_[GreenIdx][CoreIdx] = Model::LoadObj("junction/core", true); // 核
	spModels_[GreenIdx][ShellIdx] = Model::LoadObj("junction/shell", true); // 殻
}

#pragma endregion

#pragma region Drawer

void JunctionDrawer::Initialize(Transform* pParent, const Type& type)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(Model::Object::Create({}, spVP_, nullptr, nullptr, nullptr, nullptr));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset(type);
}

void JunctionDrawer::Reset(const Type& type)
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

	if (type == Type::eGreen)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGreen);
		pMaterial = CoreColor::MaterialPtr();
	}
	//else if (type == Type::eRed)
	//{
	//	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eRed);
	//	pMaterial = CoreColor::MaterialPtr();
	//}

	modelObjs_[CoreIdx]->SetColor(pColor);
	modelObjs_[CoreIdx]->SetMaterial(pMaterial);
}

void JunctionDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void JunctionDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

#pragma endregion