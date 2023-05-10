#include "TaskScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YScene::TaskScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み

void TaskScene::Load()
{
	// モデル
	pCube_ = Model::CreateCube();
	pSphere_ = Model::LoadObj("sphere", true);
}

#pragma endregion


#pragma region 初期化

void TaskScene::Initialize()
{
	// ビュープロジェクション初期化
	transferVP_.Initialize({ {0.0f, 20.0f, -100.0f} });

	// 光源グル－プ初期化
	lightGroup_.reset(LightGroup::Create());
	lightGroup_->SetDirectionalLightActive(0, true);
	lightGroup_->SetDirectionalLightDirection(0, Vector3(-1.0f, +1.0f, -1.0f).Normalized());
	lightGroup_->SetDirectionalLightColor(0, Vector3(1.0f, 1.0f, 1.0f));

	// 色初期化
	color_.reset(Color::Create({ 1.0f,0.0f,0.0f,1.0f }));

	// マテリアル初期化
	material_.reset(Material::Create(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f)));

	// オブジェクト初期化
	cubeObj_.reset(Model::Object::Create(
		{ {+30.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}, {10.0f,10.0f,10.0f} },
		&transferVP_,
		color_.get(),
		lightGroup_.get(),
		material_.get()));
	sphereObj_.reset(Model::Object::Create(
		{ {-30.0f,0.0f,0.0f}, {}, {10.0f,10.0f,10.0f} },
		&transferVP_,
		color_.get(),
		lightGroup_.get(),
		material_.get()));
}

#pragma endregion


#pragma region 終了処理

void TaskScene::Finalize()
{

}

#pragma endregion


#pragma region 更新

void TaskScene::Update()
{
	// 回転
	cubeObj_->rota_.x_ += 0.005f;
	if (cubeObj_->rota_.y_ >= 2.0f * PI) { cubeObj_->rota_.x_ -= 2.0f * PI; }
	cubeObj_->rota_.y_ += 0.005f;
	if (cubeObj_->rota_.y_ >= 2.0f * PI) { cubeObj_->rota_.y_ -= 2.0f * PI; }
	cubeObj_->rota_.z_ += 0.005f;
	if (cubeObj_->rota_.y_ >= 2.0f * PI) { cubeObj_->rota_.z_ -= 2.0f * PI; }

	// 行列更新
	cubeObj_->UpdateMatrix();
	sphereObj_->UpdateMatrix();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();


	// スペースキーでシェーダー切り替え
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		if (shaderType_ == Model::ShaderType::ePhong) { shaderType_ = Model::ShaderType::eToon; }
		else if (shaderType_ == Model::ShaderType::eToon) { shaderType_ = Model::ShaderType::ePhong; }
	}
}

#pragma endregion


#pragma region 描画

void TaskScene::Draw()
{
	// モデル描画
	pCube_->SetDrawCommand(cubeObj_.get(), DrawLocation::Center, shaderType_);
	pSphere_->SetDrawCommand(sphereObj_.get(), DrawLocation::Center, shaderType_);
}

#pragma endregion