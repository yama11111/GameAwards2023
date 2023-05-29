#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"
#include "YGameTransitionFactory.h"
#include "StageConfig.h"

#pragma region 名前空間宣言
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	// 基底クラス初期化処理
	if (YFramework::Initialize() == false) { return false; }

	// ステージ設定
	StageConfig::GetInstance()->Initialize();

	// シーンファクトリー設定
	sceneExe_->SetFactory(new YGameSceneFactory(), new YGameTransitionFactory());

	// シーンエグゼクティブ初期化
	sceneExe_->Initialize(YGameSceneFactory::Title_, YGameTransitionFactory::Blackout_);


	pPostEffect_ = PostEffect::Create({}, { Texture::CreateRender() });
	postEffectObject_.reset(PostEffect::Object::Create({ { WinSize.x_ / 2.0f,WinSize.y_ / 2.0f ,0.0f }, {}, {1.0f,1.0f,0.0f} }));


	pMousePointerSpr = Sprite2D::Create({ true, {}, {0.0f,0.0f} }, { Texture::Load("UI/mousePointer.png") });
	mousePointerObject_.reset(Sprite2D::Object::Create({ {}, {}, {0.5f,0.5f,0.0f} }));

	bool isShow = false;

#ifdef _DEBUG
	
	isShow = true;

#endif // DEBUG
	
	ShowCursor(isShow);

	return true;
}

void MyGame::Finalize()
{
	// 基底クラス終了処理
	YFramework::Finalize();
}

void MyGame::Update()
{
	// 基底クラス更新処理
	YFramework::Update();

	// マウス位置更新
	mousePointerObject_->pos_ = { Mouse::GetInstance()->Pos().x_, Mouse::GetInstance()->Pos().y_, 0.0f };
	mousePointerObject_->UpdateMatrix();

	// ------------------- 終了処理 ------------------- //
	// ------------------------------------------------ //
}

void MyGame::Draw()
{
	// デスクリプターヒープセット
	descHeap_.SetDrawCommand();

	pPostEffect_->StartRender();

	
	
	pPostEffect_->EndRender();

	//pPostEffect_->SetDrawCommand(postEffectObject_.get());
	//pPostEffect_->SetDrawCommand(postEffectObject_.get(), PostEffect::ShaderType::eBloom);

	// 描画準備
	dx_.PreDraw(ClearColor);

	// スクリーン設定セット
	screenDesc_.SetDrawCommand();
	
	// ゲームシーン描画
	DrawGameScene();
	
	// ポストエフェクト描画
	PostEffect::Pipeline::StaticDraw();

	// ポストエフェクト描画セットクリア
	PostEffect::Pipeline::StaticClearDrawSet();

#ifdef _DEBUG

	// imgui描画
	imguiMan_.Draw();

#endif // DEBUG

	// 描画後処理
	dx_.PostDraw();
}

void MyGame::DrawGameScene()
{
	// シーン描画
	sceneExe_->Draw();

	// マウス描画
	pMousePointerSpr->SetDrawCommand(mousePointerObject_.get(), DrawLocation::Front);

	// 描画場所の数だけ
	for (size_t i = 0; i < DrawLocationNum; i++)
	{
		// 変換
		DrawLocation location = static_cast<DrawLocation>(i);


		// モデル描画
		Model::Pipeline::StaticDraw(location);

		// スプライト3D描画
		Sprite3D::Pipeline::StaticDraw(location);

		// スプライト2D描画
		Sprite2D::Pipeline::StaticDraw(location);


		// モデル描画セットクリア
		Model::Pipeline::StaticClearDrawSet(location);

		// スプライト3D描画セットクリア
		Sprite3D::Pipeline::StaticClearDrawSet(location);

		// スプライト2D描画セットクリア
		Sprite2D::Pipeline::StaticClearDrawSet(location);
	}
}
