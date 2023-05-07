#include "RelayBug.h"

using YGame::IParticleModel;
using YGame::RelayBug;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

void RelayBug::Emit(
	const uint32_t startToRelayFrame,
	const uint32_t relayToEndFrame,
	const Vector3& start,
	const Vector3& relay,
	const Vector3& end,
	const Vector3& rota,
	const Vector3& scale,
	const Vector3& color,
	YGame::Model* pModel, const DrawLocation& location)
{
	// モデルポインタ代入
	pModel_ = pModel;

	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(startToRelayFrame + relayToEndFrame, location);
	IParticleModel::CreateObject();

	// オブジェクト初期化
	obj_->Initialize({ {}, rota, scale });

	// 色初期化
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// 開始地点 から 中継地点 までのフラグ を true に
	isStartToRelay_ = true;

	// 開始地点 から 中継地点 までのタイマー
	startToRelayTim_.Initialize(startToRelayFrame);

	// タイマー開始
	startToRelayTim_.SetActive(true);


	// 中継地点 から 終了地点 までのフラグ
	isRelayToEnd_ = false;

	// 中継地点 から 終了地点 までのタイマー
	relayToEndTim_.Initialize(relayToEndFrame);


	// 位置イージング
	posEas_.Initialize(start, relay, 3.0f);

	// 終了位置
	end_ = end;
}

void RelayBug::Update()
{
	// 生命更新
	if (IParticle::UpdateLife() == false) { return; }

	// 割合
	float ratio = 0.0f;

	// 開始地点 から 中継地点 なら
	if (isStartToRelay_)
	{
		// タイマー更新
		startToRelayTim_.Update();

		// 割合保存
		ratio = startToRelayTim_.Ratio();

		// イーズアウト
		obj_->pos_ = posEas_.Out(ratio);

		// タイマーが終了したら
		if (startToRelayTim_.IsEnd())
		{
			// 開始地点 から 中継地点 を終了
			isStartToRelay_ = false;

			// 中継地点 から 終了地点 を開始
			isRelayToEnd_ = true;

			// 位置イージング初期化
			posEas_.Initialize(obj_->pos_, end_, 3.0f);

			// タイマー開始
			relayToEndTim_.SetActive(true);
		}
	}
	// 中継地点 から 終了地点なら
	else if (isRelayToEnd_)
	{
		// タイマー更新
		relayToEndTim_.Update();

		// 割合保存
		ratio = relayToEndTim_.Ratio();

		// イーズイン
		obj_->pos_ = posEas_.In(ratio);
	}

	// Object更新
	obj_->UpdateMatrix();
}

void RelayBug::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_);
}