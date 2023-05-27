#include "Block.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

#include <imgui.h>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Block::spKeys_ = nullptr;
void Block::StaticInitialize()
{
	// キーインスタンス取得
	spKeys_ = YInput::Keys::GetInstance();
}

void Block::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), BlockDrawerCommon::Type::eWhite);

	// リセット
	Reset(signIndex, pos);
}

void Block::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// 前回左上位置初期化
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// スピード初期化
	speed_ = {};


	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ LevelData::Block::CollRadSize });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eBlock);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);


	// マップチップコライダー初期化
	YukiMapchipCollider::Initialize();
	trfm_ = *transform_;

	// マップチップコライダー半径設定
	radius_ = { GetBox2DRadSize().x_, GetBox2DRadSize().y_, 0.0f};

	// マップチップコライダーインデックス設定
	idxSign_ = signIndex;


	// 描画クラスリセット
	drawer_.Reset(BlockDrawerCommon::Type::eWhite);
}

Vector3& Block::PosRef()
{
	return transform_->pos_;
}

Vector3& Block::SpeedRef()
{
	return speed_;
}

void Block::Move()
{
	// スキル発動時のみ
	if (GetIsActSkill() == false) { return; }

	// x軸移動
	speed_.x_ += spKeys_->Horizontal() * LevelData::Player::Acceleration;

	// スキル終了
	SetIsActSkill(false);
}

void Block::Landing()
{
	// 重力をなくす
	speed_.y_ = 0.0f;

	// 着地した瞬間なら
	if (IsLandingMoment())
	{

	}
}

void Block::UpdatePhysics()
{
	// ゴールした後は無視
	//if (isGoal_) { return; }

	// 持ってたら弾く
	if (spStageMan_->isHoldSignVector_[idxSign_]) { return; }

	// 移動
	Move();

	// 摩擦力
	if (speed_.x_ > 0.0f)
	{
		speed_.x_ -= LevelData::Player::Friction;
		speed_.x_ = (std::max)(0.0f, speed_.x_);
	}
	if (speed_.x_ < 0.0f)
	{
		speed_.x_ += LevelData::Player::Friction;
		speed_.x_ = (std::min)(0.0f, speed_.x_);
	}

	// 重力
	speed_.y_ -= LevelData::Player::Gravity;

	// クランプ
	speed_.x_ = Clamp(speed_.x_, -LevelData::Player::MaxSpeed.x_, +LevelData::Player::MaxSpeed.x_);
	speed_.y_ = Clamp(speed_.y_, -LevelData::Player::MaxGravity, +LevelData::Player::MaxSpeed.y_);
}

void Block::OnCollision(ObjectCollider* pPair)
{

}

void Block::Draw()
{
	// 描画
	drawer_.Draw();
}

void Block::Update()
{
	// 代入
	trfm_.pos_ = transform_->pos_;
	velocity_ = speed_;

	// 判定
	spStageMan_->CallPPC(this);

	// 戻す
	*transform_ = trfm_;
	speed_ = velocity_;
}

void Block::PreUpdate()
{
	// 看板インデックス更新
	SetSignIndex(idxSign_);

	// 左上更新
	UpdateLeftTop();

	// 座標更新
	YukiMapchipCollider::UpdatePos();

	// 物理挙動更新
	UpdatePhysics();
	
	// 持ってたら弾く
	if (spStageMan_->isHoldSignVector_[idxSign_] == false)
	{
		// 着地フラグ初期化
		ResetIsLanding();
	}

	// マップチップコライダー更新
	Update();


	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Block::PostUpdate()
{
	// 着地時
	if (IsLanding())
	{
		// 着地
		Landing();
	}

	// 持ってたら弾く
	if (spStageMan_->isHoldSignVector_[idxSign_] == false) 
	{
		// 移動
		transform_->pos_ += speed_;
	}

	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}
