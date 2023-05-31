#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#include "SceneExecutive.h"

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

array<array<unique_ptr<CBColor>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sColors_;
array<array<unique_ptr<CBMaterial>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sMates_;

array<array<Vector3, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sColorValues_;
array<array<Vector3, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sMateValues_;

Power CoreColor::sFlickeringPow_;
bool CoreColor::sIsSwitchFlickeringPow_ = false;
Ease<float> CoreColor::sFlickeringColorRateEas_;

bool CoreColor::sIsUnify_ = false;
Timer CoreColor::sUnifyTim_;
array<array<Ease<Vector3>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sUnifyColorEass_;
array<array<Ease<Vector3>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sUnifyMateEass_;

#pragma endregion

#pragma region Index

static const size_t CoreIdx = static_cast<size_t>(CoreColor::PartsType::eCore);
static const size_t ShellIdx = static_cast<size_t>(CoreColor::PartsType::eShell);

#pragma endregion


void CoreColor::StaticInitialize()
{
	// 生成
	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// 色
			sColors_[i][j].reset(CBColor::Create());

			// マテリアル
			sMates_[i][j].reset(CBMaterial::Create());
		}
	}

	// 色値
	sColorValues_ = 
	{
		{
			{
				Core::Color::Gray, Core::Color::Red, Core::Color::Green, Core::Color::Blue, Core::Color::Orange
			},
			{
				Shell::Color::Gray, Shell::Color::Red, Shell::Color::Green, Shell::Color::Blue, Shell::Color::Orange
			}
		}
	};

	// マテリアル値
	sMateValues_ =
	{
		{
			{
				Core::Material::Gray, Core::Material::Red, Core::Material::Green, Core::Material::Blue, Core::Material::Orange
			},
			{
				Shell::Material::Gray, Shell::Material::Red, Shell::Material::Green, Shell::Material::Blue, Shell::Material::Orange
			}
		}
	};


	// 明滅パワー
	sFlickeringPow_.Initialize(Flickering::Frame);

	// 明滅色イージング
	sFlickeringColorRateEas_.Initialize(Flickering::Start, Flickering::End, Flickering::Exponent);


	// 色統一用タイマー
	sUnifyTim_.Initialize(Unify::Frame);

	// リセット
	StaticReset();
}

void CoreColor::StaticReset()
{
	// 初期化
	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// アルファ値
			//sColors_[CoreIdx][j]->SetAlpha(0.75f);
			
			// 色
			sColors_[i][j]->SetRGB(sColorValues_[i][j]);

			// マテリアル
			sMates_[i][j]->SetAmbient(sMateValues_[i][j]);


			// 色イージング
			sUnifyColorEass_[i][j].Initialize({}, {}, 0.0f);

			// マテリアルイージング
			sUnifyMateEass_[i][j].Initialize({}, {}, 0.0f);
		}
	}


	// 明滅パワーリセット
	sFlickeringPow_.Reset();

	// 明滅パワースイッチオン
	sIsSwitchFlickeringPow_ = true;


	// 色統一用フラグ
	sIsUnify_ = false;

	// 色統一用タイマー
	sUnifyTim_.Reset(false);
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

	// 色毎に
	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// 設定色, マテリアル
			Vector3 color{}, mate{};

			// 統一中なら
			if (sIsUnify_)
			{
				// イーズイン
				color = sUnifyColorEass_[i][j].In(sUnifyTim_.Ratio()) * rate;
				mate  = sUnifyMateEass_[i][j].In(sUnifyTim_.Ratio());
			}
			// それ以外なら
			else
			{
				// 値 * 割合
				color = sColorValues_[i][j] * rate;
				mate  = sMateValues_[i][j];
			}

			// 更新
			sColors_[i][j]->SetRGB(color);
			sMates_[i][j]->SetAmbient(mate);
		}
	}

	// 統一後終了
	if (sUnifyTim_.IsEnd())
	{
		YScene::SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 10, 10);
	}
}

void CoreColor::StaticClearAnimation(const ColorType colorType)
{
	// 統一開始
	sIsUnify_ = true;

	// インデックス
	size_t idx = static_cast<size_t>(colorType);

	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		// 最終値設定
		Vector3 endColor = Vector3(sColorValues_[i][idx]);
		Vector3 endMate = Vector3(sMateValues_[i][idx]);
		
		// 色の数だけ
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// 初期値設定
			Vector3 startColor = sColorValues_[i][j];
			Vector3 startMate = sMateValues_[i][j];

			// 色統一用イージング初期化
			sUnifyColorEass_[i][j].Initialize(startColor, endColor, Unify::Exponent);

			// マテリアル統一用イージング初期化
			sUnifyMateEass_[i][j].Initialize(startMate, endMate, Unify::Exponent);
		}
	}

	// タイマーリセット + 開始
	sUnifyTim_.Reset(true);
}

CBColor* CoreColor::ColorPtr(const ColorType colorType, const PartsType partsType)
{
	// インデックス
	size_t colorIdx = static_cast<size_t>(colorType);
	size_t partsIdx = static_cast<size_t>(partsType);

	// 色ポインタを返す
	return sColors_[partsIdx][colorIdx].get();
}

CBMaterial* CoreColor::MaterialPtr(const ColorType colorType, const PartsType partsType)
{
	// インデックス
	size_t colorIdx = static_cast<size_t>(colorType);
	size_t partsIdx = static_cast<size_t>(partsType);

	// マテリアルポインタを返す
	return sMates_[partsIdx][colorIdx].get();
}
