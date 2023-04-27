#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"
#include "Def.h"

using std::unique_ptr;
using YGame::ParticleManager;
using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YMath::Ease;
using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

void ParticleManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// 基底クラス
	IParticle::StaticInitialize(pVP);

	// ----- モデル設定 ----- //
	
	// 煙
	Smoke::StaticInitialize(Model::Load("grid", false));
	
	// リレー虫
	RelayBug::StaticInitialize(Model::Load("grid", false));
	
	// 泡グリッド
	Bubble::StaticInitialize(Model::Load("grid", false));
	
}

void ParticleManager::Initialize()
{
	// パーティクル全削除
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// パーティクル死んだら削除
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });

	// パーティクル毎更新
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	// パーティクル描画
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw();
	}
}

void ParticleManager::EmitSmoke(
	const size_t& emitNum,
	const uint32_t& aliveFrame,
	const Vector3& center, const Vector3& range,
	const float& minScale, const float& maxScale,
	const Vector3& minMoveSpeed, const Vector3& maxMoveSpeed,
	const Vector3& minRotaSpeed, const Vector3& maxRotaSpeed,
	const Vector3& color,
	const float& place)
{
	// その数だけ
	for (size_t i = 0; i < emitNum; i++)
	{
		// パーティクル生成
		unique_ptr<Smoke> newParticle = std::make_unique<Smoke>();


		// 設定用ステータス
		Transform::Status status;

		// 範囲にランダムな位置
		Vector3 randRange(
			GetRand(-range.x_, +range.x_, place),
			GetRand(-range.y_, +range.y_, place),
			GetRand(-range.z_, +range.z_, place));

		// 中心 + ランダム範囲の位置に
		status.pos_ = center + randRange;

		// ランダムなサイズ取得
		float scaleSize = GetRand(minScale, maxScale, place);

		// ランダムなサイズ適応
		status.scale_ = Vector3(scaleSize, scaleSize, scaleSize);


		// ランダムな移動スピード
		Vector3 moveSpeed(
			GetRand(minMoveSpeed.x_, maxMoveSpeed.x_, place),
			GetRand(minMoveSpeed.y_, maxMoveSpeed.y_, place),
			GetRand(minMoveSpeed.z_, maxMoveSpeed.z_, place));


		// ランダムな回転スピード
		Vector3 rotaSpeed(
			GetRand(minRotaSpeed.x_, maxRotaSpeed.x_, place),
			GetRand(minRotaSpeed.y_, maxRotaSpeed.y_, place),
			GetRand(minRotaSpeed.z_, maxRotaSpeed.z_, place));


		// 発生
		newParticle->Emit(aliveFrame, status, moveSpeed, rotaSpeed, color);

		// 挿入
		particles_.push_back(std::move(newParticle));
	}
}

void ParticleManager::EmitRelayBug(
	const size_t& emitNum,
	const uint32_t& startToRelayFrame, const uint32_t& relayToEndFrame,
	const Vector3& start, const Vector3& end,
	const Vector3& relayRange,
	const Vector3& minRota, const Vector3& maxRota,
	const float& minScale, const float& maxScale,
	const Vector3& color,
	const float& place)
{
	// その数だけ
	for (size_t i = 0; i < emitNum; i++)
	{
		// パーティクル生成
		unique_ptr<RelayBug> newParticle = std::make_unique<RelayBug>();


		// 範囲
		Vector3 randRange(
			GetRand(-relayRange.x_, +relayRange.x_, place),
			GetRand(-relayRange.y_, +relayRange.y_, place),
			GetRand(-relayRange.z_, +relayRange.z_, place));

		// 中継地点
		Vector3 relay = start + randRange;


		// ランダムなサイズ取得
		float scaleSize = GetRand(minScale, maxScale, place);

		// ランダムなスケール
		Vector3 scale = Vector3(scaleSize, scaleSize, scaleSize);


		// ランダムな回転
		Vector3 rota(
			GetRand(minRota.x_, maxRota.x_, place),
			GetRand(minRota.y_, maxRota.y_, place),
			GetRand(minRota.z_, maxRota.z_, place));


		// 発生
		newParticle->Emit(startToRelayFrame, relayToEndFrame, start, relay, end, rota, scale, color);

		// 挿入
		particles_.push_back(std::move(newParticle));
	}
}

void ParticleManager::EmitBubbleGrid(
	const size_t& emitNum,
	const uint32_t& aliveFrame,  
	const Vector3& center, const Vector3& range, 
	const float& minScale, const float& maxScale,
	const Vector3& minMoveSpeed, const Vector3& maxMoveSpeed, 
	const Vector3& minRotaSpeed, const Vector3& maxRotaSpeed, 
	const Vector3& color,
	const float& place)
{
	// 発生数だけ
	for (size_t i = 0; i < emitNum; i++)
	{
		// パーティクル生成
		unique_ptr<Bubble> newParticle = std::make_unique<Bubble>();


		// 設定用ステータス
		Transform::Status status;

		// 範囲にランダムな位置
		Vector3 randRange(
			GetRand(-range.x_, +range.x_, place),
			GetRand(-range.y_, +range.y_, place),
			GetRand(-range.z_, +range.z_, place));

		// 中心 + ランダム範囲の位置に
		status.pos_ = center + randRange;

		// ランダムなサイズ取得
		float scaleSize = GetRand(minScale, maxScale, place);

		// ランダムなサイズ適応
		status.scale_ = Vector3(scaleSize, scaleSize, scaleSize);


		// ランダムな移動スピード
		Vector3 moveSpeed(
			GetRand(minMoveSpeed.x_, maxMoveSpeed.x_, place),
			GetRand(minMoveSpeed.y_, maxMoveSpeed.y_, place),
			GetRand(minMoveSpeed.z_, maxMoveSpeed.z_, place));


		// ランダムな回転スピード
		Vector3 rotaSpeed(
			GetRand(minRotaSpeed.x_, maxRotaSpeed.x_, place),
			GetRand(minRotaSpeed.y_, maxRotaSpeed.y_, place),
			GetRand(minRotaSpeed.z_, maxRotaSpeed.z_, place));


		// 発生
		newParticle->Emit(aliveFrame, status, moveSpeed, rotaSpeed, color);

		// 挿入
		particles_.push_back(std::move(newParticle));
	}
}
