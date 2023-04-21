#include "GridDrawer.h"
#include "DrawerConfig.h"
#include <cassert>

using YGame::Model;
using YGame::ModelObject;
using YGame::Color;
using YMath::Vector3;
using namespace DrawerConfig::Grid;

YGame::Model* GridDrawerCommon::spGridMod_ = nullptr;
YGame::ViewProjection* GridDrawerCommon::spVP_;

void GridDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);

	// 代入
	spVP_ = pVP;

	// グリッドモデル読み込み
	spGridMod_ = Model::Load("grid", false);
}

void GridDrawer::Initalize(const YMath::Vector3& leftTop, const YMath::Vector3& num, const float scaleSize)
{
	// 色生成
	color_.reset(Color::Create());

	// クリア
	grids_.clear();

	// グリッドブロックの配置
	for (size_t y = 0; y < static_cast<size_t>(num.y_); y++)
	{
		for (size_t x = 0; x < static_cast<size_t>(num.x_); x++)
		{
			for (size_t z = 0; z < static_cast<size_t>(num.z_); z++)
			{
				// 大きさ
				Vector3 sca = { scaleSize, scaleSize, scaleSize };

				// 位置
				Vector3 pos = { (scaleSize * 4.0f) * x, -(scaleSize * 4.0f) * y, (scaleSize * 4.0f) * z };


				// モデル用オブジェクト
				std::unique_ptr<ModelObject> newObj;
				newObj.reset(ModelObject::Create({ leftTop + pos, {}, sca }, spVP_, color_.get(), nullptr, nullptr));

				// 末尾に挿入
				grids_.push_back(std::move(newObj));
			}
		}
	}

	// パワー
	alphaPow_.Initialize(Alpha::Frame);

	// イージング
	alphaEas_.Initialize(Alpha::Start, Alpha::End, Alpha::Exponent);


	// リセット
	Reset();
}

void GridDrawer::Reset()
{
	// アルファ値アニメーションをするか
	isActAlpha_ = false;

	// アルファ値スイッチャー
	isSwitchAlpha_ = false;

	// パワー
	alphaPow_.Reset();
	
	// 色初期化
	color_->SetRGB(DefColor);
}

void GridDrawer::ActAlphaAnimation()
{
	// リセット
	Reset();

	// アルファ値アニメーション開始
	isActAlpha_ = true;
}

void GridDrawer::UpdateAlphaAnimation()
{
	// アニメーションしないなら弾く
	if (isActAlpha_ == false) { return; }

	// アルファ値パワー更新
	alphaPow_.Update(isSwitchAlpha_);

	// 代入用アルファ値
	float alpha = 0.0f;

	// スイッチオンなら
	if (isSwitchAlpha_) 
	{
		// イーズイン
		alpha = alphaEas_.Out(alphaPow_.Ratio()); 
	}
	// それ以外なら
	else
	{
		// イーズアウト
		alpha = alphaEas_.In(alphaPow_.Ratio());
	}

	// アルファ値設定
	color_->SetAlpha(alpha);


	// アルファ値パワーが最大なら
	if (alphaPow_.IsMax())
	{
		// スイッチオフ
		isSwitchAlpha_ = false;
	}
	// アルファ値パワーがゼロなら
	else if (alphaPow_.IsZero())
	{
		// スイッチオン
		isSwitchAlpha_ = true;
	}
}

void GridDrawer::Update()
{
	// アルファ値アニメーション更新
	UpdateAlphaAnimation();


	// グリッド毎更新
	for (std::unique_ptr<ModelObject>& grid : grids_)
	{
		grid->UpdateMatrix();
	}
}

void GridDrawer::Draw()
{
	// グリッド毎描画
	for (std::unique_ptr<ModelObject>& grid : grids_)
	{
		spGridMod_->Draw(grid.get());
	}
}
