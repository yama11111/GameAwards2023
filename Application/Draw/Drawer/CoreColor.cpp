#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::CBColor;
using YGame::CBMaterial;

using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::CoreColorConfig;

#pragma endregion

#pragma region Static

array<unique_ptr<CBColor>, CoreColor::sTypeNum_> CoreColor::sColors_;
array<Vector3, CoreColor::sTypeNum_> CoreColor::sColorValues_;
unique_ptr<CBMaterial> CoreColor::sMate_;

Power CoreColor::sFlickeringPow_;
bool CoreColor::sIsSwitchFlickeringPow_ = false;
Ease<float> CoreColor::sFlickeringColorRateEas_;

bool CoreColor::sIsUnify_ = false;
Timer CoreColor::sUnifyTim_;
array<Ease<Vector3>, CoreColor::sTypeNum_> CoreColor::sUnifyColorEass_;
Ease<Vector3> CoreColor::sUnifyMaterialEas_;

#pragma endregion

void CoreColor::StaticInitialize(const bool isPlay)
{
	// 色
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// 生成
		sColors_[i]. reset(CBColor::Create());
	}

	// 色値
	sColorValues_ = { Color::Normal, Color::Movable, Color::Spring, Color::Clear };

	// マテリアル
	sMate_.reset(CBMaterial::Create(Ambient::Normal));


	// 色統一用タイマー
	sUnifyTim_.Initialize(Unify::Frame);


	// 明滅パワー
	sFlickeringPow_.Initialize(Flickering::Frame);

	// 明滅色イージング
	sFlickeringColorRateEas_.Initialize(Flickering::Start, Flickering::End, Flickering::Exponent);

	// リセット
	StaticReset();
}

void CoreColor::StaticReset()
{
	// 色の数だけ
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// 核色初期化
		sColors_[i] ->SetRGB(sColorValues_[i]);
		
		// 核色値初期化
		sUnifyColorEass_[i].Initialize({}, {}, 0.0f);
	}

	// 核マテリアル値初期化
	sMate_->SetAmbient(Ambient::Normal);
	
	// 核マテリアル値初期化
	sUnifyMaterialEas_.Initialize({}, {}, 0.0f);


	// 色統一用フラグ
	sIsUnify_ = false;

	// 色統一用タイマー
	sUnifyTim_.Reset(false);


	// 明滅パワーリセット
	sFlickeringPow_.Reset();

	// 明滅パワースイッチオン
	sIsSwitchFlickeringPow_ = true;
}

void CoreColor::StaticUpdate()
{
	// アルファ値パワー更新
	sFlickeringPow_.Update(sIsSwitchFlickeringPow_);

	// 保存用割合
	float rate = 0.0f;

	// スイッチオンなら
	if (sIsSwitchFlickeringPow_)
	{
		// イーズアウト
		rate = sFlickeringColorRateEas_.Out(sFlickeringPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズイン
		rate = sFlickeringColorRateEas_.In(sFlickeringPow_.Ratio());
	}

	// パワーがマックスなら
	if (sFlickeringPow_.IsMax())
	{
		// スイッチオン
		sIsSwitchFlickeringPow_ = false;
	}
	// パワーがゼロなら
	else if (sFlickeringPow_.IsZero())
	{
		// スイッチオフ
		sIsSwitchFlickeringPow_ = true;
	}

	// タイマー更新
	sUnifyTim_.Update();

	// 核色毎に
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// 設定色
		Vector3 color{};
		
		// 統一中なら
		if (sIsUnify_)
		{
			// イーズイン
			color = sUnifyColorEass_[i].In(sUnifyTim_.Ratio()) * rate;
		}
		// それ以外なら
		else
		{
			// 色値 * 割合
			color = sColorValues_[i] * rate;
		}

		// 色更新
		sColors_[i]->SetRGB(color);
	}

	// 統一中なら
	if (sIsUnify_)
	{
		// イーズイン
		sMate_->SetAmbient(sUnifyMaterialEas_.In(sUnifyTim_.Ratio()));
	}
}

void CoreColor::StaticClearAnimation(const ColorType& colorType)
{
	// 統一開始
	sIsUnify_ = true;

	// インデックス
	size_t idx = static_cast<size_t>(colorType);

	// 最終値設定
	Vector3 end = Vector3(sColorValues_[idx]);

	// 色の数だけ
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// 初期値設定
		Vector3 start = sColorValues_[i];

		// 色統一用イージング初期化
		sUnifyColorEass_[i].Initialize(start, end, Unify::Exponent);
	}

	// マテリアル統一用イージング初期化
	sUnifyMaterialEas_.Initialize(Ambient::Normal, Ambient::Clear, Unify::Exponent);

	// タイマーリセット + 開始
	sUnifyTim_.Reset(true);
}

CBColor* CoreColor::ColorPtr(const ColorType& colorType)
{
	// インデックス
	size_t idx = static_cast<size_t>(colorType);

	// 色ポインタを返す
	return sColors_[idx].get();
}

CBColor* CoreColor::ColorPtr(const size_t& index)
{
	// インデックス
	size_t idx = index;

	// クランプ
	if (idx <= 0) { idx = 0; }
	if (idx >= sColors_.size() - 1) { idx = sColors_.size() - 1; }

	// 色ポインタを返す
	return sColors_[idx].get();
}

CBMaterial* CoreColor::MaterialPtr()
{
	// マテリアルポインタを返す
	return sMate_.get();
}
