#include "Sprite2DObject.h"
#include "CalcTransform.h"
#include <cassert>
#include <memory>

#pragma region 名前空間

using YGame::Sprite2DObject;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion

#pragma region Sprite2DObject

Sprite2DObject* Sprite2DObject::Create(const Status& status)
{
	// インスタンスを返す
	return Create(status, nullptr);
}

Sprite2DObject* Sprite2DObject::Create(const Status& status, Color* pColor)
{
	// インスタンス生成 (動的)
	Sprite2DObject* instance = new Sprite2DObject();

	// 定数バッファ生成
	instance->cBuff_.Create();

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetColor(pColor);

	// インスタンスを返す
	return instance;
}

void Sprite2DObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex)
{
	// 行列
	cBuff_.map_->matWorld_ = m_ * common_.sProjection_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);
}

void Sprite2DObject::SetColor(Color* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = common_.sDefColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}

#pragma endregion


#pragma region Common

YMath::Matrix4 Sprite2DObject::Common::sProjection_ = YMath::Matrix4::Identity();
std::unique_ptr<YGame::Color> Sprite2DObject::Common::sDefColor_ = nullptr;

void Sprite2DObject::Common::StaticInitialize()
{
	// プロジェクション行列を設定
	sProjection_ = YMath::MatOrthoGraphic();

	// 生成
	sDefColor_.reset(Color::Create());
}

#pragma endregion



