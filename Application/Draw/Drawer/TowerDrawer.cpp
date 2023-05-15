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

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Tower;

#pragma endregion

#pragma region Static

array<array<Model*, TowerDrawerCommon::PartsNum_>, IMode::sTypeNum_> TowerDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr, 
};
YGame::ViewProjection* TowerDrawerCommon::spVP_ = nullptr;
CBMaterial* TowerDrawerCommon::spMate_ = nullptr;

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Core); // 核
static const size_t ShellIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Shell); // 殻

#pragma endregion

#pragma region Common

void TowerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::CBMaterial* pMate)
{
	// nullチェック
	assert(pVP);
	assert(pMate);
	// 代入
	spVP_ = pVP;
	spMate_ = pMate;

	// ----- モデル読み込み ----- //

	// 通常
	spModels_[IMode::sNormalIdx][CoreIdx] = Model::LoadObj("tower/normal/core", true); // 核
	spModels_[IMode::sNormalIdx][ShellIdx] = Model::LoadObj("tower/normal/shell", true); // 殻

	// 赤
	spModels_[IMode::sMovableIdx][CoreIdx] = Model::LoadObj("tower/red/core", true); // 核
	spModels_[IMode::sMovableIdx][ShellIdx] = Model::LoadObj("tower/red/shell", true); // 殻
}

#pragma endregion

#pragma region Drawer

void TowerDrawer::Initialize(YMath::Matrix4* pParent, const IMode::Type& modeType)
{
	// nullチェック
	assert(pParent);

	// オブジェクト生成 + 親行列挿入
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = pParent;

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(Model::Object::Create({}, spVP_, nullptr, nullptr, spMate_, nullptr));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset(modeType);
}

void TowerDrawer::Reset(const IMode::Type& modeType)
{
	// 核
	core_->Initialize({});

	// 基底モード初期化
	IMode::ChangeType(modeType);

	// オブジェクト初期化(パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// 核の色とマテリアル設定
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CurrentTypeIndex()));
}

void TowerDrawer::Update()
{
	// 行列更新 (親)
	core_->UpdateMatrix();

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void TowerDrawer::Draw(const YGame::DrawLocation& location)
{
	// 描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[CurrentTypeIndex()][i]->SetDrawCommand(modelObjs_[i].get(), location);
	}
}

#pragma endregion