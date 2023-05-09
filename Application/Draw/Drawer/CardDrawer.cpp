#include "CardDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "StageConfig.h"
#include <cassert>
#include <cmath>

#pragma region 名前空間

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2D;
using YGame::Texture;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Card;

#pragma endregion

std::array<YGame::Sprite2D*, 10> CardDrawerCommon::spNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
YGame::Sprite2D* CardDrawerCommon::spCardSpr_ = nullptr;

void CardDrawerCommon::StaticInitialize()
{
	// ----- スプライト読み込み ----- //

	// 数字
	spNumberSpr_[0] = Sprite2D::Create({}, { Texture::Load("Numbers/0.png", false) });
	spNumberSpr_[1] = Sprite2D::Create({}, { Texture::Load("Numbers/1.png", false) });
	spNumberSpr_[2] = Sprite2D::Create({}, { Texture::Load("Numbers/2.png", false) });
	spNumberSpr_[3] = Sprite2D::Create({}, { Texture::Load("Numbers/3.png", false) });
	spNumberSpr_[4] = Sprite2D::Create({}, { Texture::Load("Numbers/4.png", false) });
	spNumberSpr_[5] = Sprite2D::Create({}, { Texture::Load("Numbers/5.png", false) });
	spNumberSpr_[6] = Sprite2D::Create({}, { Texture::Load("Numbers/6.png", false) });
	spNumberSpr_[7] = Sprite2D::Create({}, { Texture::Load("Numbers/7.png", false) });
	spNumberSpr_[8] = Sprite2D::Create({}, { Texture::Load("Numbers/8.png", false) });
	spNumberSpr_[9] = Sprite2D::Create({}, { Texture::Load("Numbers/9.png", false) });

	// ステージカード
	spCardSpr_ = Sprite2D::Create({}, { Texture::Load("Select/card.png", false) });
}

void CardDrawer::Initialize(YGame::Transform* pParent, const int number)
{
	// 数字
	// 0以下なら弾く
	assert(number > 0);
	// 代入
	number_ = number;

	// ----- 生成 ----- //

	// 核
	core_.reset(new Transform());
	core_->parent_ = &pParent->m_;

	// 色
	color_.reset(Color::Create());

	// ステージカードオブジェクト
	cardObjs_.reset(Sprite2D::Object::Create({}, color_.get()));
	cardObjs_->parent_ = &core_->m_;

	// 数字用オブジェクト
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		numObjs_[i].reset(Sprite2D::Object::Create({}, color_.get()));
		numObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void CardDrawer::Reset()
{
	// ブヨブヨアニメーション初期化
	SlimeActor::Initialize();

	// ----- オブジェクト初期化 ----- //

	// 核
	core_->Initialize({});

	// 数字
	{
		// 大きさ
		float scale = 0.5f;

		numObjs_[0]->Initialize({ {0.0f,0.0f,0.0f},{},{scale,scale,0.0f} });

		// 幅
		float x = 16.0f;

		numObjs_[1]->Initialize({ {+x,0.0f,0.0f},{},{scale,scale,0.0f} });
		numObjs_[2]->Initialize({ {-x,0.0f,0.0f},{},{scale,scale,0.0f} });
	}

	// カード
	cardObjs_->Initialize({});

	// 色初期化
	color_->SetRGBA({ 1.0f,1.0f,1.0f,1.0f });

	// ----- アニメーション ----- //

	// 選択されているか
	isSelected_ = false;
	// 選択されていたか
	isElderSelected_ = false;
	// 決定されたか
	isDetermined_ = false;
	
	// 移動用イージング
	moveEas_.Initialize(0.0f, Animation::Move::ValueX, Animation::Move::Exponent);
	// 拡大用イージング
	scaleEas_.Initialize(0.0f, Animation::Scale::Value, Animation::Scale::Exponent);
	// 選択用パワー
	selectPow_.Initialize(Animation::Frame);
}

void CardDrawer::UpdateSelectAnimation()
{
	// ----- ブヨブヨアニメーション ----- //
	
	// 選択された瞬間
	if (isSelected_ && isElderSelected_ == false)
	{
		// 伸縮量
		Vector3 val = core_->scale_ * SlimeAction::Value;

		// 潰し伸ばし
		Vector3 squash = +val;
		Vector3 streach = -val;

		// 時間
		unsigned int frame = SlimeAction::Frame;
		// 指数
		float exponent = SlimeAction::Exponent;

		// 動作する
		SlimeActor::Activate(
			{ 
				{ {}, frame, exponent},
				{ streach, frame, exponent },
				{ squash, frame, exponent },
				{ {}, frame, exponent }
			}
		);
	}

	// 選択を記録
	isElderSelected_ = isSelected_;


	// -------- アニメーション --------- //

	// 選択中ならパワー更新
	selectPow_.Update(isSelected_);
	
	// ----- 移動 ----- //

	// 移動量
	float moveVal = 0.0f;
	
	// 選ばれているなら
	if (isSelected_)
	{
		// イーズイン代入
		moveVal = moveEas_.In(selectPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズアウト代入
		moveVal = moveEas_.Out(selectPow_.Ratio());
	}

	// 移動量代入
	core_->pos_.x_ = moveVal;

	
	// ----- 拡大 ----- //

	// 移動量
	float scaleVal = 0.0f;

	// 選ばれているなら
	if (isSelected_)
	{
		// イーズイン代入
		scaleVal = scaleEas_.In(selectPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズアウト代入
		scaleVal = scaleEas_.Out(selectPow_.Ratio());
	}

	// 移動量代入
	core_->scale_ = Vector3(1.0f, 1.0f, 1.0f) + Vector3(scaleVal, scaleVal, 0.0f);


	
	// -------------- 色 -------------- //

	// 色の値
	Vector3 colorVal = {};

	// 選ばれているなら
	if (isSelected_)
	{
		// 通常色に
		colorVal = { 1.0f,1.0f,1.0f };
	}
	// それ以外なら
	else
	{
		// 暗い色に
		colorVal = { 0.25f,0.25f,0.25f };
	}

	// 色設定
	color_->SetRGB(colorVal);
}


void CardDrawer::Update()
{
	// 選択アニメーション更新
	UpdateSelectAnimation();

	// ブヨブヨアニメーション更新
	SlimeActor::Update();

	// 核
	core_->UpdateMatrix(
		{
			{},
			{},
			SlimeActor::JiggleValue()
		}
	);

	// 数字
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		numObjs_[i]->UpdateMatrix();
	}

	// カード
	cardObjs_->UpdateMatrix();
}

void CardDrawer::Draw()
{
	// カード描画
	spCardSpr_->SetDrawCommand(cardObjs_.get(), YGame::DrawLocation::Front);

	// 数字
	// 10未満なら
	if (number_ < 10)
	{
		// 1つだけ映す
		spNumberSpr_[number_]->SetDrawCommand(numObjs_[0].get(), YGame::DrawLocation::Front);
	}
	// それ以外なら
	else
	{
		int ones = static_cast<int>(number_) % 10;
		int tens = static_cast<int>(number_) / 10;

		spNumberSpr_[ones]->SetDrawCommand(numObjs_[1].get(), YGame::DrawLocation::Front);
		spNumberSpr_[tens]->SetDrawCommand(numObjs_[2].get(), YGame::DrawLocation::Front);
	}
}

void CardDrawer::Determine()
{

	// 決定フラグを true に
	isDetermined_ = true;
}
