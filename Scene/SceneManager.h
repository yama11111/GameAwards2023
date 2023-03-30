#pragma once
#include "ISceneFactory.h"
#include "ITransitionFactory.h"

namespace YScene
{
	class SceneManager
	{
	private:
		// シーン
		std::unique_ptr<BaseScene> scene_;
		// 次のシーン
		BaseScene* nextScene_ = nullptr;
		// シーンファクトリー
		std::unique_ptr<ISceneFactory> sceneFactory_;
		// 遷移ファクトリー
		std::unique_ptr<ITransitionFactory> transitionFactory_;
	public:
		// 初期化
		void Initialize(const std::string& sceneName);
		// 終了処理
		void Finalize();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		/// <summary>
		/// 次シーン予約
		/// </summary>
		/// <param name="sceneName"> : 次シーンの名前</param>
		/// <param name="transitionName"> : 遷移の名前</param>
		void Change(const std::string& sceneName, const std::string& transitionName);
		// シーンファクトリー設定
		void SetSceneFactory(ISceneFactory* sceneFactory);
		// 遷移ファクトリー設定
		void SetSceneFactory(ITransitionFactory* transitionFactory);
	public:
		// シングルトン
		static SceneManager* GetInstance();
	private:
		SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager&) = delete;
		const SceneManager& operator=(const SceneManager&) = delete;
	};
}
