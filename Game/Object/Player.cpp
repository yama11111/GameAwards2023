#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>
#include <imgui.h>

#include "Stage.h"

using YGame::Transform;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Player::spKeys_ = nullptr;

void Player::StaticInitialize()
{
	// キーインスタンス取得
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), &direction_);

	// リセット
	Reset(signIndex, pos);
}

void Player::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });

	// スピード初期化
	speed_ = {};

	// 向き (右)
	direction_ = Vector3(+1, 0, 0);

	// ジャンプカウントリセット
	jumpCount_ = 0;


	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::ePlayer);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);


	// マップチップコライダー初期化
	YukiMapchipCollider::Initialize();
	trfm_ = *transform_;
	
	// マップチップコライダー半径設定
	radius_ = { GetBox2DRadSize().x_, GetBox2DRadSize().y_, 0.0f };


	// 落下フラグをうごかすか
	isGetOffAct_ = false;

	// 落下フラグタイマー
	isGetOffTimer_.Initialize(5);
	isGetOffTimer_.SetActive(false);

	// 描画クラスリセット
	drawer_.Reset();
}

void Player::Move()
{
	// x軸移動
	speed_.x_ += spKeys_->Horizontal();

	// クランプ
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);

	// 保存用フラグ
	bool isMove = false;

	// 移動しているなら
	if (spKeys_->Horizontal() != 0)
	{
		// フラグをtrueに
		isMove = true;

		// 向き変更
		if (speed_.x_ > 0) { direction_.x_ = +1.0f; }
		if (speed_.x_ < 0) { direction_.x_ = -1.0f; }
	}

	// 移動アニメーション
	drawer_.SetActMoveAnimation(isMove);
}

void Player::Jump()
{
	// ジャンプ回数が最大なら弾く
	if (1 <= jumpCount_) { return; }

	// 特殊アクション中なら弾く
	if (spKeys_->IsDown(DIK_E)) { return; }

	// SPACEキー押したら
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		// ジャンプ
		speed_.y_ = 1.0f;

		// ジャンプアニメーション
		drawer_.JumpAnimation();

		// ジャンプカウント
		jumpCount_++;
	}
}

void Player::Landing()
{
	// 重力をなくす
	speed_.y_ = 0.0f;

	// ジャンプカウントリセット
	jumpCount_ = 0;

	// 着地した瞬間なら
	if (IsLandingMoment() || (isGrounded_ && isOldGrounded_ == false))
	{
		// 着地アニメーション
		drawer_.LandingAnimation();
	}
}

void Player::UpdatePhysics()
{
	// ゴールした後は無視
	if (isGameClear_) { return; }

	// 移動
	Move();

	// ジャンプ
	Jump();

	// 摩擦力
	if (speed_.x_ > 0)
	{
		speed_.x_ -= 0.1f;
		speed_.x_ = (std::max)(0.0f, speed_.x_);
	}
	if (speed_.x_ < 0)
	{
		speed_.x_ += 0.1f;
		speed_.x_ = (std::min)(0.0f, speed_.x_);
	}

	// 重力
	speed_.y_ -= 0.1f;

	// クランプ
	speed_.x_ = Clamp(speed_.x_, -1.5f, +1.5f);
	speed_.y_ = Clamp(speed_.y_, -1.5f, +1.5f);
}

Vector3& Player::PosRef()
{
	return transform_->pos_;
}

Vector3& Player::SpeedRef()
{
	return speed_;
}

void Player::OnCollision(ObjectCollider* pPair)
{
	// ブロックなら
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// E でアクション
		pPair->SetIsActSkill(spKeys_->IsDown(DIK_E));
	}
	// ばねなら
	else if (pPair->GetColliderType() == ObjectCollider::Type::eSpring)
	{
		// ジャンプ
		speed_.y_ = 3.0f;

		// アクション
		pPair->SetIsActSkill(true);
	}
	// レーザーなら
	else if (pPair->GetColliderType() == ObjectCollider::Type::eLaser)
	{
		// 死ぬ
		isAlive_ = false;

		// アニメーション
		drawer_.DeadAnimation();
	}
	// スイッチなら
	else if (pPair->GetColliderType() == ObjectCollider::Type::eSwitch)
	{
		// E でアクション
		if (spKeys_->IsTrigger(DIK_E))
		{
			pPair->SetIsActSkill(true);
		}
	}
	// ゴールなら
	else if (pPair->GetColliderType() == ObjectCollider::Type::eGoal)
	{
		// アクション
		pPair->SetIsActSkill(true);
	}
}

void Player::Draw()
{
	// 描画
	drawer_.Draw();
}

void Player::Update()
{
	// 代入
	trfm_ = *transform_;
	velocity_ = speed_;
	
	// 判定
	spStageMan_->PPC(this);
	
	// 戻す
	transform_->pos_ = trfm_.pos_;
	speed_ = velocity_;
}

void Player::PreUpdate()
{
	// 座標更新
	YukiMapchipCollider::UpdatePos();

	// 物理挙動更新
	UpdatePhysics();
	

	// 下入力 から タイマー終了まで降りる
	if (spKeys_->IsUnder())
	{
		isGetOffAct_ = true;
		isGetOffTimer_.Reset(true);
	}
	isGetOffTimer_.Update();
	if (isGetOffTimer_.IsEnd())
	{
		isGetOffAct_ = false;
	}

	// 降りるか
	SetIsGetOff(isGetOffAct_);


	// 着地フラグ初期化
	ResetIsLanding();

	// マップチップコライダー更新
	Update();
	
	
	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Player::PostUpdate()
{
	// 着地時
	if (IsLanding() || isGrounded_)
	{
		// 着地
 		Landing();
	}

	// 移動
	transform_->pos_ += speed_;

	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

