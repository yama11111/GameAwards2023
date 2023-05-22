#include "Laser.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

// デフォルト回転量
static Vector3 defRota = YMath::AdjustAngle(Vector3(0.0f, -1.0f, 0.0f).Normalized());

void Laser::Initialize(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), &beamLength_);

	// リセット
	Reset(signIndex, pos, direction);
}

void Laser::Reset(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });

	// 向き初期化
	direction_ = direction;
	
	// ビームの長さ
	beamLength_ = 0.0f;

	// ビームの長さ計算
	CalcBeamLength();

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eLaser);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);

	// 描画クラスリセット
	drawer_.Reset();
}

void Laser::PreUpdate()
{
	// ビーム長さ変更
	if (isColl_ == false) 
	{
		beamLength_ += 0.2f;
	}
	isColl_ = false;
}

void Laser::PostUpdate()
{
	// 向き計算
	Vector3 rota = YMath::AdjustAngle(direction_.Normalized());
	
	// トランスフォーム行列更新
	transform_->UpdateMatrix({ {}, defRota + rota, {} });

	// ビームの長さ計算
	CalcBeamLength();

	// 描画クラス更新
	drawer_.Update();
}

void Laser::Draw()
{
	// 描画
	drawer_.Draw();
}

void Laser::OnCollision(ObjectCollider* pPair)
{
	// ブロックなら
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock ||
		pPair->GetColliderType() == ObjectCollider::Type::eSpring ||
		pPair->GetColliderType() == ObjectCollider::Type::ePlatform)
	{
		// 中心座標とサイズ取得
		Vector2 center = pPair->GetBox2DCenter();
		Vector2 radSize = pPair->GetBox2DRadSize();

		// 向き毎に長さ計算
		if		(direction_.x_ > 0.0f)
		{
			beamLength_ = ((center.x_ - radSize.x_) - transform_->pos_.x_) / 2.0f;
		}
		else if (direction_.x_ < 0.0f)
		{
			beamLength_ = (transform_->pos_.x_ - (center.x_ + radSize.x_)) / 2.0f;
		}
		else if (direction_.y_ > 0.0f)
		{
			beamLength_ = ((center.y_ - radSize.y_) - transform_->pos_.y_) / 2.0f;
		}
		else if (direction_.y_ < 0.0f)
		{
			beamLength_ = (transform_->pos_.y_ - (center.y_ - radSize.y_)) / 2.0f;
		}

		isColl_ = true;

		CalcBeamLength();
	}
}

void Laser::CalcBeamLength()
{
	// 向きから位置とサイズ計算
	Vector2 center = { transform_->pos_.x_, transform_->pos_.y_ };
	Vector2 radSize = {};

	if (direction_.x_ != 0.0f) 
	{
		radSize.x_ = transform_->scale_.y_ * beamLength_;
		radSize.y_ = transform_->scale_.x_ / 10.0f;

		if (direction_.x_ > 0.0f)
		{
			center.x_ += radSize.x_;
		}
		else if (direction_.x_ < 0.0f)
		{
			center.x_ -= radSize.x_;
		}
	}
	else if (direction_.y_ != 0.0f) 
	{
		radSize.x_ = transform_->scale_.x_ / 10.0f;
		radSize.y_ = transform_->scale_.y_ * beamLength_;

		if (direction_.y_ > 0.0f)
		{
			center.y_ += radSize.y_;
		}
		else if (direction_.y_ < 0.0f)
		{
			center.y_ -= radSize.y_;
		}
	}

	// コライダー位置初期化
	Box2D::SetBox2DCenter(center);

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize(radSize);
}
