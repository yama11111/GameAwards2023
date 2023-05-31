#pragma once
#include "CBColor.h"
#include "CBMaterial.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include <array>
#include <memory>

class CoreColor
{

public:

	// 色種類
	enum class ColorType
	{
		eGray	 = 0, // 灰色
		eRed	 = 1, // 赤色
		eGreen	 = 2, // 緑色
		eBlue	 = 3, // 青色
		eOrange	 = 4, // 橙色
		eEnd, // リサイズ用
	};

	// パーツ種類
	enum class PartsType
	{
		eCore = 0, // 核
		eShell = 1, // 殻
		eEnd, // リサイズ用
	};

	// 色種類の数
	static const size_t sColorTypeNum_ = static_cast<size_t>(ColorType::eEnd);
	
	// パーツ種類の数
	static const size_t sPartsTypeNum_ = static_cast<size_t>(PartsType::eEnd);

private:
	
	// 色
	static std::array<std::array<std::unique_ptr<YGame::CBColor>, sColorTypeNum_>, sPartsTypeNum_> sColors_;

	// マテリアル
	static std::array<std::array<std::unique_ptr<YGame::CBMaterial>, sColorTypeNum_>, sPartsTypeNum_> sMates_;


	// 色値
	static std::array<std::array<YMath::Vector3, sColorTypeNum_>, sPartsTypeNum_> sColorValues_;

	// マテリアル値
	static std::array<std::array<YMath::Vector3, sColorTypeNum_>, sPartsTypeNum_> sMateValues_;


	// 核色明滅パワー
	static YMath::Power sFlickeringPow_;

	// 核色明滅パワースイッチ
	static bool sIsSwitchFlickeringPow_;

	// 核色明滅割合イージング
	static YMath::Ease<float> sFlickeringColorRateEas_;


	// 色統一用フラグ
	static bool sIsUnify_;

	// 色統一用タイマー
	static YMath::Timer sUnifyTim_;

	// 色統一用イージング
	static std::array<std::array<YMath::Ease<YMath::Vector3>, sColorTypeNum_>, sPartsTypeNum_ > sUnifyColorEass_;
	
	// マテリアル統一用イージング
	static std::array<std::array<YMath::Ease<YMath::Vector3>, sColorTypeNum_>, sPartsTypeNum_ > sUnifyMateEass_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的リセット
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();

public:

	/// <summary>
	/// クリア演出 (全ての色を統一する)
	/// </summary>
	/// <param name="colorType"> : 色タイプ</param>
	static void StaticClearAnimation(const ColorType colorType);

public:

	/// <summary>
	/// 色ポインタ取得
	/// </summary>
	/// <param name="colorType"> : 色のタイプ</param>
	/// <param name="partsType"> : パーツタイプ</param>
	/// <returns>対応する色のポインタ</returns>
	static YGame::CBColor* ColorPtr(const ColorType colorType, const PartsType partsType);

	/// <summary>
	/// マテリアルポインタ取得
	/// </summary>
	/// <param name="colorType"> : 色のタイプ</param>
	/// <param name="partsType"> : パーツタイプ</param>
	/// <returns>マテリアルのポインタ</returns>
	static YGame::CBMaterial* MaterialPtr(const ColorType colorType, const PartsType partsType);

};

