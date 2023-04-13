#include "InputDrawer.h"
#include "HUDConfig.h"
#include "Keys.h"

using YGame::Sprite2D;
using YGame::Sprite2DObject;
using YGame::Texture;
using YMath::Vector3;
using namespace HUDConfig::Operation;

#pragma region InputDrawerCommon

YInput::Keys* InputDrawerCommon::sKeys_ = nullptr;
Sprite2D* InputDrawerCommon::spKeyWASDSpr_  = nullptr;
Sprite2D* InputDrawerCommon::spKeyWPushSpr_ = nullptr;
Sprite2D* InputDrawerCommon::spKeyAPushSpr_ = nullptr;
Sprite2D* InputDrawerCommon::spKeySPushSpr_ = nullptr;
Sprite2D* InputDrawerCommon::spKeyDPushSpr_ = nullptr;
Sprite2D* InputDrawerCommon::spKeySDeadSpr_ = nullptr;
std::array<Sprite2D*, 2> InputDrawerCommon::spKeySpaceSpr_ = { nullptr, nullptr };
std::array<Sprite2D*, 2> InputDrawerCommon::spKeyTabSpr_ = { nullptr, nullptr };

void InputDrawerCommon::StaticInitialize()
{
	// キー
	sKeys_ = YInput::Keys::GetInstance();

	// WASD
	spKeyWASDSpr_	  = Sprite2D::Create({}, { Texture::Load("UI/key_WASD.png") });
	// WASD_PUSH
	spKeyWPushSpr_	  = Sprite2D::Create({}, { Texture::Load("UI/key_W_PUSH.png") });
	spKeyAPushSpr_	  = Sprite2D::Create({}, { Texture::Load("UI/key_A_PUSH.png") });
	spKeySPushSpr_	  = Sprite2D::Create({}, { Texture::Load("UI/key_S_PUSH.png") });
	spKeyDPushSpr_	  = Sprite2D::Create({}, { Texture::Load("UI/key_D_PUSH.png") });
	// S_DEAD
	spKeySDeadSpr_	  = Sprite2D::Create({}, { Texture::Load("UI/key_S_DEAD.png") });
	// SPACE
	spKeySpaceSpr_[0] = Sprite2D::Create({}, { Texture::Load("UI/key_SPACE.png") });
	spKeySpaceSpr_[1] = Sprite2D::Create({}, { Texture::Load("UI/key_SPACE_PUSH.png") });
	// TAB
	spKeyTabSpr_[0]	  = Sprite2D::Create({}, { Texture::Load("UI/key_TAB.png") });
	spKeyTabSpr_[1]	  = Sprite2D::Create({}, { Texture::Load("UI/key_TAB_PUSH.png") });
}

#pragma endregion


#pragma region InputDrawer

void InputDrawer::Initalize(const SceneType& sceneType)
{
	// ----- 生成 ----- //

	// WASD
	keyWASDObj_.reset(Sprite2DObject::Create({}));
	// WASD_PUSH
	keyWObj_.reset(Sprite2DObject::Create({}));
	keyAObj_.reset(Sprite2DObject::Create({}));
	keySObj_.reset(Sprite2DObject::Create({}));
	keyDObj_.reset(Sprite2DObject::Create({}));
	// SPACE
	keySpaceObj_.reset(Sprite2DObject::Create({}));
	// TAB
	keyTabObj_.reset(Sprite2DObject::Create({}));


	// リセット
	Reset(sceneType);
}

void InputDrawer::Reset(const SceneType& sceneType)
{
	// ----- Object初期化 ----- //

	// WASD (シーンの種類によって変える)
	if (sceneType == SceneType::Select)
	{
		keyWASDObj_->Initialize({ Select::Key::WASD, {}, Select::Key::Scale });
	}
	else if (sceneType == SceneType::Play)
	{
		keyWASDObj_->Initialize({ Play::Key::WASD, {}, Play::Key::Scale });
	}

	// WASD_PUSH
	keyWObj_->Initialize({ {} });
	keyAObj_->Initialize({ {} });
	keySObj_->Initialize({ {} });
	keyDObj_->Initialize({ {} });
	// parent
	keyWObj_->parent_ = &keyWASDObj_->m_;
	keyAObj_->parent_ = &keyWASDObj_->m_;
	keySObj_->parent_ = &keyWASDObj_->m_;
	keyDObj_->parent_ = &keyWASDObj_->m_;

	// SPACE (シーンの種類によって変える)
	if (sceneType == SceneType::Select)
	{
		keySpaceObj_->Initialize({ Select::Key::Space, {}, Select::Key::Scale });
	}
	else if (sceneType == SceneType::Play)
	{
		keySpaceObj_->Initialize({ Play::Key::Space, {}, Play::Key::Scale });
	}

	// TAB (シーンの種類によって変える)
	if (sceneType == SceneType::Select)
	{
		keyTabObj_->Initialize({ Select::Key::Tab, {}, Select::Key::Scale });
	}
	else if (sceneType == SceneType::Play)
	{
		keyTabObj_->Initialize({ Play::Key::Tab, {}, Play::Key::Scale });
	}


	// ----- フラグ初期化 ----- //

	// WASD
	isPushW_ = false;
	isPushA_ = false;
	isPushS_ = false;
	isPushD_ = false;
	// SPACE
	isPushSpace_ = false;
	// TAB
	isPushTab_ = false;
}

void InputDrawer::UpdatePushFlags()
{
	// WASD
	isPushW_ = sKeys_->IsDown(DIK_W);
	isPushA_ = sKeys_->IsDown(DIK_A);
	isPushS_ = sKeys_->IsDown(DIK_S);
	isPushD_ = sKeys_->IsDown(DIK_D);
	// SPACE
	isPushSpace_ = sKeys_->IsDown(DIK_SPACE);
	// TAB
	isPushTab_ = sKeys_->IsDown(DIK_TAB);
}

void InputDrawer::UpdateObjects()
{
	// WASD
	keyWASDObj_->UpdateMatrix();
	// WASD_PUSH
	keyWObj_->UpdateMatrix();
	keyAObj_->UpdateMatrix();
	keySObj_->UpdateMatrix();
	keyDObj_->UpdateMatrix();
	// SPACE
	keySpaceObj_->UpdateMatrix();
	// TAB
	keyTabObj_->UpdateMatrix();
}

void InputDrawer::Update()
{
	// フラグ更新
	UpdatePushFlags();

	// object更新
	UpdateObjects();
}

void InputDrawer::Draw(const bool isPlayer)
{
	// WASD
	spKeyWASDSpr_->Draw(keyWASDObj_.get());
	// WASD_PUSH
	if (isPushW_) { spKeyWPushSpr_->Draw(keyWObj_.get()); }
	if (isPushA_) { spKeyAPushSpr_->Draw(keyAObj_.get()); }
	if (isPushS_) { spKeySPushSpr_->Draw(keySObj_.get()); }
	if (isPushD_) { spKeyDPushSpr_->Draw(keyDObj_.get()); }
	// S_DEAD
	if (isPlayer) { spKeySDeadSpr_->Draw(keySObj_.get()); }
	// SPACE
	spKeySpaceSpr_[isPushSpace_]->Draw(keySpaceObj_.get());
	// TAB
	spKeyTabSpr_[isPushTab_]->Draw(keyTabObj_.get());
}

#pragma endregion
