#include "InputDrawer.h"
#include "HUDConfig.h"

#include "SceneManager.h"
#include "YGameSceneFactory.h"

#include "PilotManager.h"

#pragma region 名前空間

using YGame::Transform;
using YGame::Sprite2D;
using YGame::Texture;
using YGame::UIButtonDrawer;
using YGame::UIChargeButtonDrawer;
using YScene::SceneManager;
using YScene::YGameSceneFactory;
using YMath::Vector3;
using namespace HUDConfig::Operation;

#pragma endregion

#pragma region Static

YInput::Keys* InputDrawerCommon::sKeys_ = nullptr;
YInput::Mouse* InputDrawerCommon::sMouse_ = nullptr;
UIButtonDrawer InputDrawerCommon::spKeyW_;
UIButtonDrawer InputDrawerCommon::spKeyA_;
UIButtonDrawer InputDrawerCommon::spKeyS_;
UIButtonDrawer InputDrawerCommon::spKeyD_;
UIButtonDrawer InputDrawerCommon::spKeyE_;
UIButtonDrawer InputDrawerCommon::spKeyF_;
UIChargeButtonDrawer InputDrawerCommon::spKeyR_;
UIButtonDrawer InputDrawerCommon::spKeySpace_;
UIButtonDrawer InputDrawerCommon::spMouseL_;
UIButtonDrawer InputDrawerCommon::spKeyEsc_;
bool InputDrawerCommon::isPlayer_ = false;

#pragma endregion

#pragma region InputDrawerCommon

void InputDrawerCommon::StaticInitialize()
{

	UIChargeButtonDrawer::StaticInitialize();

	// キー
	sKeys_ = YInput::Keys::GetInstance();

	// マウス
	sMouse_ = YInput::Mouse::GetInstance();
	
	// WASD
	spKeyW_.Initialize(Texture::Load("UI/key_W.png"), Texture::Load("UI/key_W_PUSH.png"), Texture::Load("UI/key_W_DEAD.png"));
	spKeyA_.Initialize(Texture::Load("UI/key_A.png"), Texture::Load("UI/key_A_PUSH.png"), Texture::Load("UI/key_A_DEAD.png"));
	spKeyS_.Initialize(Texture::Load("UI/key_S.png"), Texture::Load("UI/key_S_PUSH.png"), Texture::Load("UI/key_S_DEAD.png"));
	spKeyD_.Initialize(Texture::Load("UI/key_D.png"), Texture::Load("UI/key_D_PUSH.png"), Texture::Load("UI/key_D_DEAD.png"));

	// E
	spKeyE_.Initialize(Texture::Load("UI/key_E.png"), Texture::Load("UI/key_E_PUSH.png"), Texture::Load("UI/key_E_DEAD.png"));
	// F
	spKeyF_.Initialize(Texture::Load("UI/key_F.png"), Texture::Load("UI/key_F_PUSH.png"));
	// R
	spKeyR_.Initialize(Texture::Load("UI/key_R.png"), Texture::Load("UI/key_R_PUSH.png"), nullptr, 60);

	// LEFT
	spMouseL_.Initialize(Texture::Load("UI/mouse_LEFT.png"), Texture::Load("UI/mouse_LEFT_PUSH.png"), Texture::Load("UI/mouse_LEFT_DEAD.png"));
	
	// SPACE
	spKeySpace_.Initialize(Texture::Load("UI/key_SPACE.png"), Texture::Load("UI/key_SPACE_PUSH.png"), Texture::Load("UI/key_SPACE_DEAD.png"));
	
	// ESC
	spKeyEsc_.Initialize(Texture::Load("UI/key_ESC.png"), Texture::Load("UI/key_ESC_PUSH.png"));

	// プレイヤー操作
	isPlayer_ = true;
}

void InputDrawerCommon::StaticUpdate()
{
	// WASD 押したか更新
	spKeyW_.Update(sKeys_->IsUp());
	spKeyA_.Update(sKeys_->IsLeft());
	spKeyS_.Update(sKeys_->IsUnder());
	spKeyD_.Update(sKeys_->IsRight());

	// EFR 押したか更新
	spKeyE_.Update(sKeys_->IsDown(DIK_E));
	spKeyF_.Update(sKeys_->IsDown(DIK_F));

	if (PilotManager::StaticGetIsActInit() == false)
	{
		spKeyR_.Update(sKeys_->IsDown(DIK_R));
	}

	// SPACE 押したか更新
	spKeySpace_.Update(sKeys_->IsDown(DIK_SPACE));

	// ESCAPE 押したか更新
	spKeyEsc_.Update(sKeys_->IsDown(DIK_ESCAPE));

	// Mouse 押したか更新
	spMouseL_.Update(sMouse_->IsDown(YInput::MouseClick::DIM_LEFT));

	// WASD
	spKeyW_.SetIsDead(!isPlayer_);
	spKeyA_.SetIsDead(!isPlayer_);
	spKeyS_.SetIsDead(!isPlayer_);
	spKeyD_.SetIsDead(!isPlayer_);

	// E
	spKeyE_.SetIsDead(!isPlayer_);

	// SPACE
	spKeySpace_.SetIsDead(!isPlayer_);

	// Mouse
	spMouseL_.SetIsDead(isPlayer_);
}

#pragma endregion

#pragma region InputDrawer

void InputDrawer::Initialize()
{
	// ----- 生成 ----- //

	// WASD
	keyWObj_.reset(Sprite2D::Object::Create());
	keyAObj_.reset(Sprite2D::Object::Create());
	keySObj_.reset(Sprite2D::Object::Create());
	keyDObj_.reset(Sprite2D::Object::Create());

	// EFR
	keyEObj_.reset(Sprite2D::Object::Create());
	keyFObj_.reset(Sprite2D::Object::Create());
	keyRObj_.reset(Sprite2D::Object::Create());
	
	// SPACE
	keySpaceObj_.reset(Sprite2D::Object::Create());
	
	// LEFT
	mouseLObj_.reset(Sprite2D::Object::Create());
	
	// ESC
	keyEscObj_.reset(Sprite2D::Object::Create());


	// リセット
	Reset();
}

void InputDrawer::Reset()
{
	// ----- Object初期化 ----- //

	// 位置保存用
	Vector3 w, a, s, d, e, f, r, space, left, esc;

	// 大きさ
	Vector3 scale;

	// シーンの種類によって変える
	if		(SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Title_)
	{
		w = Title::Key::W;
		a = Title::Key::A;
		s = Title::Key::S;
		d = Title::Key::D;

		e = Title::Key::E;
		f = Title::Key::F;
		r = Title::Key::R;

		space = Title::Key::Space;

		left = Title::Mouse::Left;

		esc = Title::Key::Esc;

		scale = Title::Key::Scale;
	}
	else if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Select_)
	{
		w = Select::Key::W;
		a = Select::Key::A;
		s = Select::Key::S;
		d = Select::Key::D;

		e = Select::Key::E;
		f = Select::Key::F;
		r = Select::Key::R;

		space = Select::Key::Space;

		left = Select::Mouse::Left;

		esc = Select::Key::Esc;

		scale = Select::Key::Scale;
	}
	else if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Play_)
	{
		w = Play::Key::W;
		a = Play::Key::A;
		s = Play::Key::S;
		d = Play::Key::D;

		e = Play::Key::E;
		f = Play::Key::F;
		r = Play::Key::R;

		space = Play::Key::Space;

		left = Play::Mouse::Left;

		esc = Play::Key::Esc;

		scale = Play::Key::Scale;
	}

	// WASD
	keyWObj_->Initialize({ w, {}, scale });
	keyAObj_->Initialize({ a, {}, scale });
	keySObj_->Initialize({ s, {}, scale });
	keyDObj_->Initialize({ d, {}, scale });

	// EFR
	keyEObj_->Initialize({ e, {}, scale });
	keyFObj_->Initialize({ f, {}, scale });
	keyRObj_->Initialize({ r, {}, scale });

	// SPACE
	keySpaceObj_->Initialize({ space, {}, scale });
	
	// LEFT
	mouseLObj_->Initialize({ left, {}, scale });

	//ESC
	keyEscObj_->Initialize({ esc, {}, scale });

}

void InputDrawer::Update()
{
	// WASD
	keyWObj_->UpdateMatrix();
	keyAObj_->UpdateMatrix();
	keySObj_->UpdateMatrix();
	keyDObj_->UpdateMatrix();

	// EFR
	keyEObj_->UpdateMatrix();
	keyFObj_->UpdateMatrix();
	keyRObj_->UpdateMatrix();

	// SPACE
	keySpaceObj_->UpdateMatrix();
	
	// LEFT
	mouseLObj_->UpdateMatrix();

	// TAB
	keyEscObj_->UpdateMatrix();
}

void InputDrawer::Draw()
{
	// WASD
	spKeyW_.Draw(keyWObj_.get());
	spKeyA_.Draw(keyAObj_.get());
	spKeyS_.Draw(keySObj_.get());
	spKeyD_.Draw(keyDObj_.get());

	// EFR
	spKeyE_.Draw(keyEObj_.get());
	spKeyF_.Draw(keyFObj_.get());
	spKeyR_.Draw(keyRObj_.get());
	
	// SPACE
	spKeySpace_.Draw(keySpaceObj_.get());
	
	// LEFT
	spMouseL_.Draw(mouseLObj_.get());
	
	// TAB
	spKeyEsc_.Draw(keyEscObj_.get());
}

#pragma endregion
