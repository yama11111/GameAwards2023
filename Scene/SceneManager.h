#pragma once
#include "ISceneFactory.h"
#include "ITransitionFactory.h"

namespace YScene
{
	class SceneManager
	{
	private:
		// �V�[��
		std::unique_ptr<BaseScene> scene_;
		// ���̃V�[��
		BaseScene* nextScene_ = nullptr;
		// �V�[���t�@�N�g���[
		std::unique_ptr<ISceneFactory> sceneFactory_;
		// �J�ڃt�@�N�g���[
		std::unique_ptr<ITransitionFactory> transitionFactory_;
	public:
		// ������
		void Initialize(const std::string& sceneName);
		// �I������
		void Finalize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		/// <summary>
		/// ���V�[���\��
		/// </summary>
		/// <param name="sceneName"> : ���V�[���̖��O</param>
		/// <param name="transitionName"> : �J�ڂ̖��O</param>
		void Change(const std::string& sceneName, const std::string& transitionName);
		// �V�[���t�@�N�g���[�ݒ�
		void SetSceneFactory(ISceneFactory* sceneFactory);
		// �J�ڃt�@�N�g���[�ݒ�
		void SetSceneFactory(ITransitionFactory* transitionFactory);
	public:
		// �V���O���g��
		static SceneManager* GetInstance();
	private:
		SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager&) = delete;
		const SceneManager& operator=(const SceneManager&) = delete;
	};
}
