#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Color;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::CoreColorConfig;

#pragma endregion

#pragma region Static

array<unique_ptr<Color>, CoreColor::sTypeNum_> CoreColor::sColors_;
array<Vector3, CoreColor::sTypeNum_> CoreColor::sColorValues_;
array<Ease<Vector3>, CoreColor::sTypeNum_> CoreColor::sColorValueEass_;

Power CoreColor::sFlickeringPow_;
bool CoreColor::sIsSwitchFlickeringPow_ = false;
Ease<float> CoreColor::sFlickeringColorRateEas_;

#pragma endregion

void CoreColor::StaticInitialize()
{
	// 色
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// 生成
		sColors_[i]. reset(Color::Create());
	}

	// 色値
	sColorValues_ = { Normal, Movable, Clear };

	// 明滅パワー
	sFlickeringPow_.Initialize(Flickering::Frame);

	// 明滅色イージング
	sFlickeringColorRateEas_.Initialize(Flickering::Start, Flickering::End, Flickering::Exponent);

	// リセット
	StaticReset();
}

void CoreColor::StaticReset()
{
	// 核色初期化
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		sColors_[i] ->SetRGB(sColorValues_[i]);
	}

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

	// 核色毎に
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// 設定色
		Vector3 color = sColorValues_[i] * rate;

		// 色更新
		sColors_[i]->SetRGB(color);
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
}

Color* CoreColor::ColorPtr(const ColorType& colorType)
{
	// インデックス
	size_t idx = static_cast<size_t>(colorType);

	// 色ポインタを返す
	return sColors_[idx].get();
}

Color* CoreColor::ColorPtr(const size_t& idx)
{
	// 0以下 か 最大値を超える なら弾く
	assert(0 <= idx);
	assert(idx < sColors_.size());

	// 色ポインタを返す
	return sColors_[idx].get();
}
