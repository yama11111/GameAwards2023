#include "IDrawer.h"
#include <cassert>

#pragma region 名前空間

using YGame::Transform;
using YGame::Color;
using YGame::SlimeActor;

#pragma endregion

YGame::ParticleManager* IDrawer::spParticleMan_ = nullptr;

void IDrawer::StaticInitialize(YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pParticleMan);
	// 代入
	spParticleMan_ = pParticleMan;
}

void IDrawer::Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime)
{
	// nullチェック
	assert(pParent);
	// 代入
	pParent_ = pParent;

	// オブジェクト生成 + 親行列挿入
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = &pParent->m_;

	// 色生成
	color_.reset(Color::Create());

	// 立ちモーションタイマー初期化
	idleTim_.Initialize(intervalTime);

	// リセット
	Reset(mode);
}

void IDrawer::Reset(const Mode& mode)
{
	// 初期化
	SlimeActor::Initialize();

	// オブジェクト初期化
	core_->Initialize({});

	// 現在の状態
	current_ = mode;
	// 変更後の状態
	next_ = Mode::None;

	// 立ちモーションタイマーリセット
	idleTim_.Reset(true);
}

void IDrawer::Update(const YGame::Transform::Status& status)
{
	// 立ちモーションタイマー更新
	idleTim_.Update();

	// タイマーが終わったら
	if (idleTim_.IsEnd())
	{
		// 立ちモーション再生
		IdleAnimation();
		// タイマーリセット
		idleTim_.Reset(true);
	}
	
	// 行列更新 (親)
	core_->UpdateMatrix(
		{
			-SlimeActor::JiggleValue() + status.pos_,
			status.rota_,
			SlimeActor::JiggleValue() + status.scale_
		}
	);
}
