#include "UIChargeButtonDrawer.h"
#include "MathUtillity.h"

using YGame::UIChargeButtonDrawer;

YGame::Sprite2D* UIChargeButtonDrawer::spChargeGauge_ = nullptr;
std::unique_ptr<YGame::CBColor> UIChargeButtonDrawer::sChargeGaugeColor_;

void UIChargeButtonDrawer::Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex, const unsigned int frame)
{
	// 初期化
	UIButtonDrawer::Initialize(pButtonTex, pPressedTex, pDeadTex);

	// パワー初期化
	chargePower_.Initialize(frame);

	float width = static_cast<float>(pButtonTex->Buffer()->GetDesc().Width);
	float height = static_cast<float>(pButtonTex->Buffer()->GetDesc().Height) / 8.0f;

	// イージング初期化
	chargeWidthEase_.Initialize(0.0f, width, 1.0f);

	chargeGaugeObj_.reset(Sprite2D::Object::Create());
	chargeGaugeObj_->SetColor(sChargeGaugeColor_.get());

	chargeGaugeObj_->scale_ = { 0.0f, height, 0.0f };
	chargeGaugeObj_->pos_ = { 0.0f, height * 5.0f, 0.0f };
}

void UIChargeButtonDrawer::Update(const bool isPush)
{
	UIButtonDrawer::Update(isPush);

	chargePower_.Update(isPush);
	
	chargeGaugeObj_->scale_.x_ = chargeWidthEase_.In(chargePower_.Ratio());
	chargeGaugeObj_->pos_.x_ = chargeGaugeObj_->scale_.x_ / 2.0f - 32.0f;

	chargeGaugeObj_->UpdateMatrix();
}

void UIChargeButtonDrawer::Draw(Sprite2D::Object* pObject)
{
	// 死んでいたら
	if (isDead_)
	{
		// デッドボタン描画
		pDeadButtonSpr_->SetDrawCommand(pObject, DrawLocation::Front);
	}
	else
	{
		// ボタン描画
		pButtonSpr_[isPush_]->SetDrawCommand(pObject, DrawLocation::Front);

		chargeGaugeObj_->parent_ = &pObject->m_;
		chargeGaugeObj_->UpdateMatrix();
		chargeGaugeObj_->parent_ = nullptr;

		spChargeGauge_->SetDrawCommand(chargeGaugeObj_.get(), DrawLocation::Front);
	}
}

void UIChargeButtonDrawer::StaticInitialize()
{
	spChargeGauge_ = Sprite2D::Create({}, { Texture::Load("white1x1.png") });
	sChargeGaugeColor_.reset(CBColor::Create());
	sChargeGaugeColor_->SetRGBA(YMath::GetColor(48, 226, 170, 255));
}
