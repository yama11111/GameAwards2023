#include "InputDrawer.h"
#include "HUDConfig.h"
//#include "Keys.h"

#include "SceneManager.h"
#include "YGameSceneFactory.h"

#pragma region 名前空間

using YGame::Transform;
using YGame::Sprite2D;
using YGame::Texture;
using YGame::UIButtonDrawer;
using YScene::SceneManager;
using YScene::YGameSceneFactory;
using YMath::Vector3;
using namespace HUDConfig::Operation;

#pragma endregion

#pragma region Static

YInput::Keys* InputDrawerCommon::sKeys_ = nullptr;

UIButtonDrawer InputDrawerCommon::spKeyW_;
UIButtonDrawer InputDrawerCommon::spKeyA_;
UIButtonDrawer InputDrawerCommon::spKeyS_;
UIButtonDrawer InputDrawerCommon::spKeyD_;

UIButtonDrawer InputDrawerCommon::spKeySpace_;

UIButtonDrawer InputDrawerCommon::spKeyEsc_;

#pragma endregion

#pragma region InputDrawerCommon

void InputDrawerCommon::StaticInitialize()
{
	// キー
	sKeys_ = YInput::Keys::GetInstance();
	
	// WASD
	spKeyW_.Initialize(Texture::Load("UI/key_W.png"), Texture::Load("UI/key_W_PUSH.png"));
	spKeyA_.Initialize(Texture::Load("UI/key_A.png"), Texture::Load("UI/key_A_PUSH.png"));
	spKeyS_.Initialize(Texture::Load("UI/key_S.png"), Texture::Load("UI/key_S_PUSH.png"));
	spKeyD_.Initialize(Texture::Load("UI/key_D.png"), Texture::Load("UI/key_D_PUSH.png"));
	
	// SPACE
	spKeySpace_.Initialize(Texture::Load("UI/key_SPACE.png"), Texture::Load("UI/key_SPACE_PUSH.png"));
	
	// ESC
	spKeyEsc_.Initialize(Texture::Load("UI/key_ESC.png"), Texture::Load("UI/key_ESC_PUSH.png"));
}

void InputDrawerCommon::StaticUpdate()
{
	// WASD 押したか更新
	spKeyW_.Update(sKeys_->IsUp());
	spKeyA_.Update(sKeys_->IsLeft());
	spKeyS_.Update(sKeys_->IsUnder());
	spKeyD_.Update(sKeys_->IsRight());

	// SPACE 押したか更新
	spKeySpace_.Update(sKeys_->IsDown(DIK_SPACE));

	// ESCAPE 押したか更新
	spKeyEsc_.Update(sKeys_->IsDown(DIK_ESCAPE));
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
	
	// SPACE
	keySpaceObj_.reset(Sprite2D::Object::Create());
	
	// ESC
	keyEscObj_.reset(Sprite2D::Object::Create());


	// リセット
	Reset();
}

void InputDrawer::Reset()
{
	// ----- Object初期化 ----- //

	// 位置保存用
	Vector3 w, a, s, d, space, esc;

	// 大きさ
	Vector3 scale;

	// シーンの種類によって変える
	if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Title_)
	{
		w = Key::Title::W;
		a = Key::Title::A;
		s = Key::Title::S;
		d = Key::Title::D;

		space = Key::Title::Space;

		esc = Key::Title::Esc;

		scale = Key::Title::Scale;
	}
	else if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Select_)
	{
		w = Key::Select::W;
		a = Key::Select::A;
		s = Key::Select::S;
		d = Key::Select::D;

		space = Key::Select::Space;

		esc = Key::Select::Esc;

		scale = Key::Select::Scale;
	}
	else if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Play_)
	{
		w = Key::Play::W;
		a = Key::Play::A;
		s = Key::Play::S;
		d = Key::Play::D;

		space = Key::Play::Space;

		esc = Key::Play::Esc;

		scale = Key::Play::Scale;
	}

	// WASD
	keyWObj_->Initialize({ w, {}, scale });
	keyAObj_->Initialize({ a, {}, scale });
	keySObj_->Initialize({ s, {}, scale });
	keyDObj_->Initialize({ d, {}, scale });

	// SPACE
	keySpaceObj_->Initialize({ space, {}, scale });

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

	// SPACE
	keySpaceObj_->UpdateMatrix();

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
	
	// SPACE
	spKeySpace_.Draw(keySpaceObj_.get());
	
	// TAB
	spKeyEsc_.Draw(keyEscObj_.get());
}

#pragma endregion
