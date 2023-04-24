#include "TowerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::Material;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Tower;

#pragma endregion

#pragma region Static

array<array<Model*, TowerDrawerCommon::PartsNum_>, TowerDrawerCommon::ModeNum_> TowerDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr, 
};
YGame::ViewProjection* TowerDrawerCommon::spVP_ = nullptr;
Material* TowerDrawerCommon::spMate_ = nullptr;
array<unique_ptr<Color>, TowerDrawerCommon::ModeNum_> TowerDrawerCommon::sCoreColor_;
unique_ptr<Material> TowerDrawerCommon::sCoreMate_;
Power TowerDrawerCommon::coreColorPow_;
bool TowerDrawerCommon::isSwitchCoreColorPower_ = false;
array<Ease<Vector4>, TowerDrawerCommon::ModeNum_> TowerDrawerCommon::coreColorEas_;
#pragma endregion

#pragma region インデックス

static const size_t NormalIdx = static_cast<size_t>(TowerDrawerCommon::Mode::Normal); // 通常
static const size_t RedIdx = static_cast<size_t>(TowerDrawerCommon::Mode::Red); // 赤

static const size_t CoreIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Core); // 核
static const size_t ShellIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Shell); // 殻

#pragma endregion

#pragma region Common

void TowerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::Material* pMate)
{
	// nullチェック
	assert(pVP);
	assert(pMate);
	// 代入
	spVP_ = pVP;
	spMate_ = pMate;

	// ----- モデル読み込み ----- //

	// 通常
	spModels_[NormalIdx][CoreIdx] = Model::Load("tower/normal/core", true); // 核
	spModels_[NormalIdx][ShellIdx] = Model::Load("tower/normal/shell", true); // 殻

	// 赤
	spModels_[RedIdx][CoreIdx] = Model::Load("tower/red/core", true); // 核
	spModels_[RedIdx][ShellIdx] = Model::Load("tower/red/shell", true); // 殻


	// 色
	sCoreColor_[NormalIdx].reset(Color::Create(CoreColor::Normal::Start));
	sCoreColor_[RedIdx].reset(Color::Create(CoreColor::Red::Start));

	// マテリアル
	sCoreMate_.reset(Material::Create());

	// 核色用パワー
	coreColorPow_.Initialize(CoreColor::Frame);

	// 核色イージング
	coreColorEas_[NormalIdx].Initialize(CoreColor::Normal::Start, CoreColor::Normal::End, CoreColor::Exponent);
	coreColorEas_[RedIdx].Initialize(CoreColor::Red::Start, CoreColor::Red::End, CoreColor::Exponent);


	// リセット
	StaticReset();
}

void TowerDrawerCommon::StaticReset()
{
	// 核色用パワー
	coreColorPow_.Reset();

	// 核色パワースイッチ
	isSwitchCoreColorPower_ = true;
}

void TowerDrawerCommon::StaticUpdate()
{
	// アルファ値パワー更新
	coreColorPow_.Update(isSwitchCoreColorPower_);

	// スイッチオンなら
	if (isSwitchCoreColorPower_)
	{
		// 核色毎に
		for (size_t i = 0; i < sCoreColor_.size(); i++)
		{
			// アルファ値更新 (イーズアウト)
			sCoreColor_[i]->SetRGBA(coreColorEas_[i].Out(coreColorPow_.Ratio()));
		}
	}
	// それ以外なら
	else
	{
		// 核色毎に
		for (size_t i = 0; i < sCoreColor_.size(); i++)
		{
			// アルファ値更新 (イーズイン)
			sCoreColor_[i]->SetRGBA(coreColorEas_[i].In(coreColorPow_.Ratio()));
		}
	}

	// パワーがマックスなら
	if (coreColorPow_.IsMax())
	{
		// スイッチオン
		isSwitchCoreColorPower_ = false;
	}
	// パワーがゼロなら
	else if (coreColorPow_.IsZero())
	{
		// スイッチオフ
		isSwitchCoreColorPower_ = true;
	}
}

#pragma endregion

#pragma region Drawer

void TowerDrawer::Initialize(YMath::Matrix4* pParent, const Mode& mode)
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
		// 色ポインタ
		Color* pColor = nullptr;

		// マテリアルポインタ
		Material* pMate = nullptr;

		// 核なら
		if (i == CoreIdx)
		{
			// 普通のブロックなら
			if (mode == Mode::Normal)
			{
				// 普通色
				pColor = sCoreColor_[NormalIdx].get();
			}
			// 赤なら
			else if (mode == Mode::Red)
			{
				// 赤色
				pColor = sCoreColor_[RedIdx].get();
			}

			// デフォルトのマテリアル
			pMate = sCoreMate_.get();
		}
		// 殻なら
		else if (i == ShellIdx)
		{
			// マテリアルポインタ
			pMate = spMate_;
		}

		// 生成
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, pColor, nullptr, pMate));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset(mode);
}

void TowerDrawer::Reset(const Mode& mode)
{
	// 核
	core_->Initialize({});

	// オブジェクト初期化(パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// 状態毎に色変える
	if (mode == Mode::Normal)
	{
		modelObjs_[CoreIdx]->SetColor(sCoreColor_[NormalIdx].get());
	}
	else if (mode == Mode::Red)
	{
		modelObjs_[CoreIdx]->SetColor(sCoreColor_[RedIdx].get());
	}

	// 状態
	mode_ = mode;

	// 状態番号
	modeIdx_ = static_cast<size_t>(mode);
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

void TowerDrawer::Draw()
{
	// 描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[modeIdx_][i]->Draw(modelObjs_[i].get());
	}
}

#pragma endregion