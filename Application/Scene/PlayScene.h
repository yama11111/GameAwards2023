#pragma once
#include "BaseScene.h"

#include "Player.h"
#include "Block.h"
#include "Spring.h"
#include "Platform.h"
#include "Laser.h"
#include "Switch.h"
#include "Key.h"
#include "Goal.h"

#include "ObjectManager.h"

#include "BackGroundDrawer.h"
#include "HUDDrawer.h"

#include "Sign.h"
#include "Stage.h"
#include "Player.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{

	public:

#pragma region ���\�[�X

		// �v���CBGM
		YGame::Audio* pPlayBGM_ = nullptr;

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// ------------ �� �v���C�V�[���̕ϐ� �� ------------//
		
        //maruyama::Sign sign_;
        Stage stage_;

		// ------------ �� �v���C�V�[���̕ϐ� �� ------------//

		// �v���C���[
		std::unique_ptr<Player> player_;

		// �u���b�N
		std::list<std::unique_ptr<Block>> blocks_;

		// �΂�
		std::list<std::unique_ptr<Spring>> springs_;

		// ����
		std::list<std::unique_ptr<Platform>> platforms_;

		// ���[�U�[
		std::list<std::unique_ptr<Laser>> lasers_;

		// �X�C�b�`
		std::list<std::unique_ptr<Switch>> switches_;

		// ��
		std::list<std::unique_ptr<Key>> keys_;

		// �S�[��
		std::unique_ptr<Goal> goal_;
		
		// �M�~�b�N�t���O
		std::vector<std::unique_ptr<bool>> gimmickFlags_;

		// �I�u�W�F�N�g�}�l�[�W���[
		ObjectManager objMan_;


		// �w�i
		BackgroundDrawer background_;

		// HUD
		HUDDrawer hud_;


		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �J����
		YGame::Camera camera_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;



#pragma endregion

	public:

		/// <summary>
		/// �ǂݍ���
		/// </summary>
		void Load() override;

		/// <summary>
		/// ������
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// �I������
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		/// <summary>
		/// �J�����ʒu
		/// </summary>
		void CameraUpdate();

	public:

		// �R���X�g���N�^
		PlayScene() = default;

		// �f�X�g���N�^
		~PlayScene() = default;

	};
}
