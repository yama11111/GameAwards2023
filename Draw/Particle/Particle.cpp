#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::IlluminationGridBlock;
using YGame::PlaceGridBlock;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* IlluminationGridBlock::spModel_ = nullptr;
Model* PlaceGridBlock::spModel_ = nullptr;

#pragma region IParticle


void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;
}

void IParticle::Initialize(const uint32_t aliveTime)
{
	// 生存フラグ
	isAlive_ = true;

	// 生存タイマー初期化 + 開始
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	// 生成
	color_.reset(Color::Create());
	obj_.reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
}

bool IParticle::UpdateLife()
{
	// 死んでいるなら弾く
	if (isAlive_ == false) { return false; }

	// 生存タイマー更新
	aliveTim_.Update();
	// 生存タイマー終了 → 死亡
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	// 生きているか返す
	return isAlive_;
}

#pragma endregion


#pragma region IlluminationGridBlock

void IlluminationGridBlock::Emit(
	const uint32_t aliveTime,
	YMath::Matrix4* pParent,
	const YMath::Vector3& color,
	const YMath::Ease<float> alphaEas)
{
	// ---------- Object ---------- //
	
	// 基底クラス初期化
	IParticle::Initialize(aliveTime);

	// 親行列代入
	obj_->parent_ = pParent;

	// 少し大きく
	obj_->scale_ += Vector3(+0.05f, +0.05f, +0.05f);

	// 色初期化
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// アルファ値用パワー
	alphaPow_.Initialize(aliveTime / 2);

	// アルファ値パワーを動かす
	isActAlphaPower_ = true;

	// アルファ値イージング代入
	alphaEas_ = alphaEas;
}

void IlluminationGridBlock::Update()
{
	// 生命更新
	if (IParticle::UpdateLife() == false) { return; }

	// Object更新
	obj_->UpdateMatrix();


	// アルファ値用パワー更新
	alphaPow_.Update(isActAlphaPower_);
	
	// アルファ値用パワーが最大なら
	if (alphaPow_.IsMax())
	{
		// 更新を止める
		isActAlphaPower_ = false;
	}

	// アルファ値パワーを動かすなら
	if (isActAlphaPower_)
	{
		// アルファ値更新 (イーズアウト)
		color_->SetAlpha(alphaEas_.Out(alphaPow_.Ratio()));
	}
	// それ以外なら
	else
	{
		// アルファ値更新 (イーズイン)
		color_->SetAlpha(alphaEas_.In(alphaPow_.Ratio()));
	}
}

void IlluminationGridBlock::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}

void IlluminationGridBlock::StaticInitialize(Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

#pragma endregion


#pragma region PlaceGridBlock

void PlaceGridBlock::Emit(
	const uint32_t aliveTime, 
	YMath::Matrix4* pParent, 
	const YMath::Ease<float> scaleEas, 
	const YMath::Vector3& color)
{
	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(aliveTime);

	// 親行列代入
	obj_->parent_ = pParent;

	// 色初期化
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// 大きさイージング
	scaleEas_ = scaleEas;

}

void PlaceGridBlock::Update()
{
	// 生命更新
	if (IParticle::UpdateLife() == false) { return; }

	// 大きさイージング
	float sca = scaleEas_.Out(aliveTim_.Ratio());
	
	// 代入
	obj_->scale_ = { sca, sca, sca };

	// Object更新
	obj_->UpdateMatrix();
}

void PlaceGridBlock::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}

void PlaceGridBlock::StaticInitialize(Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

#pragma endregion


