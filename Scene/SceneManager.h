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
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="sceneName"> : 初期シーン</param>
		void Initialize(const std::string& sceneName);

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// 次シーン予約
		/// </summary>
		/// <param name="sceneName"> : 次シーンの名前</param>
		/// <param name="transitionName"> : 遷移の名前</param>
		void Change(const std::string& sceneName, const std::string& transitionName);
		

		/// <summary>
		/// シーンファクトリー設定
		/// </summary>
		/// <param name="sceneFactory"> : シーンファクトリー</param>
		void SetSceneFactory(ISceneFactory* sceneFactory);

		/// <summary>
		/// 遷移ファクトリー設定
		/// </summary>
		/// <param name="transitionFactory"> : 遷移ファクトリー</param>
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
