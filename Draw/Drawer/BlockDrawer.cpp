#include "BlockDrawer.h"
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

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

array<array<Model*, BlockDrawerCommon::PartsNum_>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
};
array<unique_ptr<Color>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::sCoreColor_;
unique_ptr<Material> BlockDrawerCommon::sCoreMate_;
Power BlockDrawerCommon::coreColorPow_;
bool BlockDrawerCommon::isSwitchCoreColorPower_ = false;
array<Ease<Vector4>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::coreColorEas_;

Model* BlockDrawerCommon::spGridModel_ = nullptr;
unique_ptr<Color> BlockDrawerCommon::sGridColor_;
unique_ptr<Material> BlockDrawerCommon::sGridMate_;
Ease<float> BlockDrawerCommon::catchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::failToCatchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::placeGridScaleValueEas_;
Ease<float> BlockDrawerCommon::failToPlaceGridScaleValueEas_;

#pragma endregion

#pragma region インデックス

static const size_t NormalIdx = static_cast<size_t>(IDrawer::Mode::Normal); // 通常
static const size_t RedIdx = static_cast<size_t>(IDrawer::Mode::Red); // 赤

static const size_t CoreIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Core); // 核
static const size_t ShellIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Shell); // 殻

#pragma endregion

#pragma region Common

void BlockDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ブロック (通常)
	spModels_[NormalIdx][CoreIdx] = Model::Load("block/normal/core", true); // 核
	spModels_[NormalIdx][ShellIdx] = Model::Load("block/normal/shell", true); // 殻

	// ブロック (赤)
	spModels_[RedIdx][CoreIdx] = Model::Load("block/red/core", true); // 核
	spModels_[RedIdx][ShellIdx] = Model::Load("block/red/shell", true); // 殻

	// グリッド
	spGridModel_ = Model::Load("grid", true);

	// ---------- モデル ---------- //

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

	// --------- グリッド --------- //

	// 色
	sGridColor_.reset(Color::Create());

	// マテリアル
	sGridMate_.reset(Material::Create());


	// 取得時大きさイージング
	catchGridScaleValueEas_.Initialize(Catch::Success::Start, Catch::Success::End, Catch::Success::Exponent);

	// 取得失敗時大きさイージング
	failToCatchGridScaleValueEas_.Initialize(Catch::Failure::Start, Catch::Failure::End, Catch::Failure::Exponent);

	// 設置時大きさイージング
	placeGridScaleValueEas_.Initialize(Place::Success::Start, Place::Success::End, Place::Success::Exponent);

	// 設置失敗時大きさイージング
	failToPlaceGridScaleValueEas_.Initialize(Place::Failure::Start, Place::Failure::End, Place::Failure::Exponent);


	// リセット
	StaticReset();
}

void BlockDrawerCommon::StaticReset()
{
	// 核色用パワー
	coreColorPow_.Reset();

	// 核色パワースイッチ
	isSwitchCoreColorPower_ = true;
}

void BlockDrawerCommon::StaticUpdate()
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

void BlockDrawer::Initialize(Transform* pParent, const Mode& mode)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

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

		// 生成
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, pColor, nullptr, pMate));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// グリッド生成
	gridObj_.reset(ModelObject::Create({}, spVP_, sGridColor_.get(), nullptr, sGridMate_.get()));

	// 親行列挿入
	gridObj_->parent_ = &core_->m_;

	// リセット
	Reset(mode);
}

void BlockDrawer::Reset(const Mode& mode)
{
	// リセット
	IDrawer::Reset(mode);

	// モデル用オブジェクト初期化
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

	// ----- アニメーション ----- //

	// 失敗用揺れ
	failureShake_.Initialize();


	// グリッド動作フラグ
	isActGrid_ = false;


	// 取得可能状態か
	isCanCatch_ = false;

	// 前は取得可能状態だったか
	isElderCanCatch_ = false;


	// 取得アニメーションをするか
	isActCatchAnimition_ = false;

	// 取得時イージング用タイマー
	catchGridTim_.Initialize(Catch::Success::Frame);

	// 取得失敗アニメーションをするか
	isActFailToCatchAnimition_ = false;

	// 取得時イージング用タイマー
	failToCatchGridTim_.Initialize(Catch::Failure::Frame);


	// 置けない状態か
	isCanPlace_ = true;

	// 前は置けない状態だったか
	isElderCanPlace_ = false;


	// 設置アニメーションをするか
	isActPlaceAnimition_ = false;

	// 設置時イージング用タイマー
	placeGridTim_.Initialize(Place::Success::Frame);
	// 設置失敗アニメーションをするか
	isActFailToPlaceAnimition_ = false;

	// 設置時イージング用タイマー
	failToPlaceGridTim_.Initialize(Place::Failure::Frame);

}

void BlockDrawer::Update()
{
	// 失敗用シェイク更新
	failureShake_.Update();

	// 基底クラス更新 
	IDrawer::Update({ failureShake_.Value() });


	// 取得可能アニメーション
	CanCatchAnimation();

	// 置けない状態アニメーション
	NotPlaceAnimation();

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}


	// グリッド動作フラグがfalseなら弾く
	if (isActGrid_ == false) { return; }

	// 大きさ
	float gridSca = 0.0f;

	// 取得アニメーションをするなら
	if (isActCatchAnimition_)
	{
		// タイマー更新
		catchGridTim_.Update();

		// イーズイン
		gridSca += catchGridScaleValueEas_.In(catchGridTim_.Ratio());

		// タイマー終了時
		if (catchGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			catchGridTim_.Reset(false);

			// 取得アニメーション終了
			isActCatchAnimition_ = false;
		}
	}
	// 取得失敗アニメーションをするなら
	if (isActFailToCatchAnimition_)
	{
		// タイマー更新
		failToCatchGridTim_.Update();

		// イーズアウト
		gridSca += failToCatchGridScaleValueEas_.Out(failToCatchGridTim_.Ratio());

		// タイマー終了時
		if (failToCatchGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			failToCatchGridTim_.Reset(false);

			// 取得失敗アニメーション終了
			isActFailToCatchAnimition_ = false;
		}
	}
	// 設置アニメーションをするなら
	if (isActPlaceAnimition_)
	{
		// タイマー更新
		placeGridTim_.Update();

		// イーズイン
		gridSca += placeGridScaleValueEas_.In(placeGridTim_.Ratio());

		// タイマー終了時
		if (placeGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			placeGridTim_.Reset(false);

			// 設置アニメーション終了
			isActPlaceAnimition_ = false;
		}
	}
	// 設置失敗アニメーションをするなら
	if (isActFailToPlaceAnimition_)
	{
		// タイマー更新
		failToPlaceGridTim_.Update();

		// イーズアウト
		gridSca += failToPlaceGridScaleValueEas_.Out(failToPlaceGridTim_.Ratio());

		// タイマー終了時
		if (failToPlaceGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			failToPlaceGridTim_.Reset(false);

			// 設置失敗アニメーション終了
			isActFailToPlaceAnimition_ = false;
		}
	}

	// グリッド更新
	gridObj_->UpdateMatrix({ {},{},Vector3(gridSca, gridSca, gridSca) });

	// フラグを更新 (全てfalseなら止める)
	isActGrid_ =
		isActCatchAnimition_ ||
		isActFailToCatchAnimition_ ||
		isActPlaceAnimition_ ||
		isActFailToPlaceAnimition_;
}

void BlockDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[CurrentModeIndex()][i]->Draw(modelObjs_[i].get());
	}

	// グリッド動作フラグがfalseなら弾く
	if (isActGrid_ == false) { return; }

	// グリッド描画
	spGridModel_->Draw(gridObj_.get());
}

void BlockDrawer::CatchAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得アニメーション開始
	isActCatchAnimition_ = true;

	// タイマーリセット + 開始
	catchGridTim_.Reset(true);
}

void BlockDrawer::FailToCatchAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得失敗アニメーション開始
	isActFailToCatchAnimition_ = true;

	// タイマーリセット + 開始
	failToCatchGridTim_.Reset(true);

	// 揺れ開始
	failureShake_.Activate(Catch::Failure::Shake::Swing, Catch::Failure::Shake::Dekey, Catch::Failure::Shake::Place);
}

void BlockDrawer::PlaceAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得アニメーション開始
	isActPlaceAnimition_ = true;

	// タイマーリセット + 開始
	placeGridTim_.Reset(true);
}

void BlockDrawer::FailToPlaceAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得失敗アニメーション開始
	isActFailToPlaceAnimition_ = true;

	// タイマーリセット + 開始
	failToPlaceGridTim_.Reset(true);

	// 揺れ開始
	failureShake_.Activate(Place::Failure::Shake::Swing, Place::Failure::Shake::Dekey, Place::Failure::Shake::Place);
}

void BlockDrawer::CanCatchAnimation()
{
	//// 取得可能か以前と違うなら
	//if (isCanCatch_ != isElderCanCatch_)
	//{
	//	// 取得可能アニメーション用タイマーリセット
	//	RetrievableTim_.Reset(false);

	//	// 取得可能なら
	//	if (isCanCatch_)
	//	{
	//		// パーティクル発生
	//		spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);
	//	}
	//}

	//// フラグ保存
	//isElderCanCatch_ = isCanCatch_;

	//// 取得可能状態じゃないなら弾く
	//if (isCanCatch_ == false) { return; }

	//// 取得可能ならタイマースタート
	//RetrievableTim_.SetActive(isCanCatch_);

	//// 取得可能タイマー更新
	//RetrievableTim_.Update();

	//// 取得可能タイマーが終了したら
	//if (RetrievableTim_.IsEnd())
	//{
	//	// パーティクル発生
	//	spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);

	//	// タイマー初期化
	//	RetrievableTim_.Reset(isCanCatch_);
	//}
}

void BlockDrawer::NotPlaceAnimation()
{
	//// 置けるか以前と違うなら
	//if (isCanPlace_ != isElderCanPlace_)
	//{
	//	// 状態毎に色初期化
	//	if (current_ == Mode::Normal)
	//	{
	//		color_->SetRGBA(DefColor::Normal);
	//	}
	//	else if (current_ == Mode::Red)
	//	{
	//		color_->SetRGBA(DefColor::Red);
	//	}
	//}

	//// フラグ保存
	//isElderCanPlace_ = isCanPlace_;

	//// 置けるなら弾く
	//if (isCanPlace_) { return; }

	//// 置けない色にする
	//color_->SetRGBA(DefColor::Invisible);
}

void BlockDrawer::IdleAnimation()
{
}

#pragma endregion