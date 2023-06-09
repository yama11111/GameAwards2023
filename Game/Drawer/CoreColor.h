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

	// 種類
	enum class ColorType
	{
		eGray	 = 0, // 灰色
		eRed	 = 1, // 赤色
		eGreen	 = 2, // 緑色
		eBlue	 = 3, // 青色
		eEnd, // リサイズ用
	};

	// 種類の数
	static const size_t sTypeNum_ = static_cast<size_t>(ColorType::eEnd);

private:
	
	// 核色
	static std::array<std::unique_ptr<YGame::CBColor>, sTypeNum_> sColors_;

	// 核色値
	static std::array<YMath::Vector3, sTypeNum_> sColorValues_;

	// マテリアル
	static std::unique_ptr<YGame::CBMaterial> sMate_;


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
	static std::array<YMath::Ease<YMath::Vector3>, sTypeNum_> sUnifyColorEass_;
	
	// マテリアル統一用イージング
	static YMath::Ease<YMath::Vector3> sUnifyMaterialEas_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize(const bool isPlay);

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
	/// <param name="colorType"> : 色のタイプ</param>
	static void StaticClearAnimation(const ColorType& colorType);

public:

	/// <summary>
	/// 色ポインタ取得
	/// </summary>
	/// <param name="colorType"> : 色のタイプ</param>
	/// <returns>対応する色のポインタ</returns>
	static YGame::CBColor* ColorPtr(const ColorType& colorType);

	/// <summary>
	/// 色ポインタ取得
	/// </summary>
	/// <param name="index"> : インデックス</param>
	/// <returns>対応する色のポインタ</returns>
	static YGame::CBColor* ColorPtr(const size_t& index);

	/// <summary>
	/// マテリアルポインタ取得
	/// </summary>
	/// <returns>マテリアルのポインタ</returns>
	static YGame::CBMaterial* MaterialPtr();

};

