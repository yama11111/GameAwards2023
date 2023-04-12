#include "Color.h"
#include "MathUtillity.h"

using YGame::Color;
using YMath::Vector4;
using YMath::Vector3;
using YMath::Clamp;

Color::Color() :
	color_(1.0f, 1.0f, 1.0f, 1.0f)
{}

Color* Color::Create(const YMath::Vector4& color, const YMath::Vector4& originalColorRate)
{
	Color* instance = new Color();
	instance->cBuff_.Create();
	instance->Initialize(color, originalColorRate);

	return instance;
}

void Color::Initialize(const YMath::Vector4& color, const YMath::Vector4& originalColorRate)
{
	SetRGBA(color);
	SetOriginalColorRateRGBA(originalColorRate);
}

void Color::SetDrawCommand(const UINT rootParamIndex)
{
	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->color_ = color_;
	cBuff_.map_->originalColorRate_ = originalColorRate_;
	// �V�F�[�_�[�ɑ���
	cBuff_.SetDrawCommand(rootParamIndex);
}


void Color::SetRGBA(const YMath::Vector4& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);

	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->color_ = color_ = Vector4(r, g, b, a);
}

void Color::SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	float a = A <= 255 ? A / 255.0f : 1.0f;
	Vector4 c = Vector4(r, g, b, a);

	SetRGBA(c);
}

void Color::SetRGB(const YMath::Vector3& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	Vector4 c = { color.x_, color.y_, color.z_, color_.a_ };

	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->color_ = color_ = c;
}

void Color::SetRGB(const UINT R, const UINT G, const UINT B)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetRGB(c);
}

void Color::SetAlpha(const float alpha)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float a = Clamp<float>(alpha, 0.0f, 1.0f);
	
	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->color_.a_ = color_.a_ = a;
}

void Color::SetAlpha(const UINT alpha)
{
	// �l�� float ��
	float a = alpha <= 255 ? alpha / 255.0f : 1.0f;

	SetAlpha(a);
}


void Color::SetOriginalColorRateRGBA(const YMath::Vector4& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.r_, 0.0f, 1.0f);
	float g = Clamp<float>(color.g_, 0.0f, 1.0f);
	float b = Clamp<float>(color.b_, 0.0f, 1.0f);
	float a = Clamp<float>(color.a_, 0.0f, 1.0f);

	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->originalColorRate_ = originalColorRate_ = Vector4(r, g, b, a);
}

void Color::SetOriginalColorRateRGBA(const UINT R, const UINT G, const UINT B, const UINT A)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	float a = A <= 255 ? A / 255.0f : 1.0f;
	Vector4 c = Vector4(r, g, b, a);

	SetOriginalColorRateRGBA(c);
}

void Color::SetOriginalColorRateRGB(const YMath::Vector3& color)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	Vector4 c = { color.x_, color.y_, color.z_, color_.a_ };

	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->originalColorRate_ = originalColorRate_ = c;
}

void Color::SetOriginalColorRateRGB(const UINT R, const UINT G, const UINT B)
{
	// �l�� float ��
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetOriginalColorRateRGB(c);
}

void Color::SetOriginalColorRateAlpha(const float alpha)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float a = Clamp<float>(alpha, 0.0f, 1.0f);

	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->originalColorRate_.a_ = originalColorRate_.a_ = a;
}

void Color::SetOriginalColorRateAlpha(const UINT alpha)
{
	// �l�� float ��
	float a = alpha <= 255 ? alpha / 255.0f : 1.0f;

	SetOriginalColorRateAlpha(a);
}