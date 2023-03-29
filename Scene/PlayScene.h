#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "Skydome.h"
#include "EffectManager.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //

		// ���n�摜
		UINT plainTex_ = 0;

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //

		// ��ʑS��
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// ----- �X�v���C�g (3D) ----- //

		// ----- ���f�� ----- //

		// �����̃��f��
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		// �v���C���[
		YGame::Transform player_;
		// ����
		YMath::Vector3 direction_;
		// �v���C���[�`��N���X
		PlayerDrawer playerDra_;

		// �t�B���^�[
		YGame::Transform filter_;
		// �t�B���^�[�`��N���X
		FilterDrawer filterDra_;

		// �u���b�N
		YGame::Transform block_;
		// �u���b�N�`��N���X
		BlockDrawer blockDra_;


		// �V��
		Skydome skydome_;

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �G�t�F�N�g�}�l�[�W���[
		YGame::EffectManager effectMan_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;

#pragma endregion
	public:
		// �ǂݍ���
		void Load() override;
		// ������
		void Initialize() override;
		// �I������
		void Finalize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	private:
		// �w�i�X�v���C�g2D�`��
		void DrawBackSprite2Ds();
		// �X�v���C�g3D�`��
		void DrawBackSprite3Ds();
		// ���f���`��
		void DrawModels();
		// �X�v���C�g3D�`��
		void DrawFrontSprite3Ds();
		// �O�i�X�v���C�g2D�`��
		void DrawFrontSprite2Ds();
	public:
		// �R���X�g���N�^
		PlayScene() = default;
		// �f�X�g���N�^
		~PlayScene() = default;

		//water�ǉ���
	private:
	};

	//class Player
	//{
	//private:
	//	Vector2 playerPos = { 0,0 };
	//	Vector2 playerSize = { 16,32 };

	//	Vector2 playerCheckPos = { 0,0 };
	//	Vector2 playerCheckSize = { 16,64 };

	//	Vector2 playerCheckSizeRL = { 16,64 };
	//	Vector2 playerCheckSizeUD = { 16,64 };

	//	//�L�[��������Ă��邩�ǂ���
	//	Vector2 DS;
	//	Vector2 AW;

	//	//�v���C���[���t�B���^�[��
	//	bool chengeF = true;

	//	//�v���C���[�����蔲���邩
	//	bool sukeF = false;
	//	//passFlag

	//	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	//	bool kadoF = false;
	//	//corner

	//public:
	//	Player();
	//	~Player();

	//	void Inilialize();
	//	void Update();
	//	void Draw();

	//	//�ʒu
	//	Vector2 GetPos() { return playerPos; };
	//	void SetPos(Vector2 nowpos) { playerPos = nowpos; };

	//	//�ŏ��̑傫��
	//	Vector2 GetSize() { return playerSize; };
	//	void SetSize(Vector2 nowsize) { playerPos = nowsize; };

	//	//���̑傫��
	//	Vector2 GetNowSizeX() { return playerCheckSizeRL; };
	//	Vector2 GetNowSizeY() { return playerCheckSizeUD; };

	//	bool GetmoveFlag() { return chengeF; };
	//	bool GetpassFlag() { return sukeF; };
	//	bool GetcornerFlag() { return kadoF; };

	//	void SetmoveFlag(bool flag) { chengeF = flag; };
	//	void SetpassFlag(bool flag) { sukeF = flag; };
	//	void SetcornerFlag(bool flag) { kadoF = flag; };
	//};

	//class Filter
	//{
	//public:
	//	Filter();
	//	~Filter();

	//	void Inilialize();
	//	void Update();
	//	void Draw();
	//private:
	//	Vector2 filterPos = { 0,0 };
	//	Vector2 filterSize = { 128,64 };
	//};

	//class Box
	//{
	//public:

	//private:
	//	Vector2 box[20];
	//	Vector2 BoxSize = { 16,16 };

	//	//�{�b�N�X�̐�
	//	int boxcount = 20;

	//	////�}�b�v��ɔz�u���Ă���u���b�N
	//	//for (int i = 0; i < boxcount; i++)
	//	//{
	//	//	box[i].x = (i * 30);
	//	//	box[i].y = (i * 30);
	//	//}

	//	////�ׂ��Ȓ���
	//	//box[19].x = (18 * 30);
	//	//box[19].y = (20 * 30);

	//	//box[15].x = (16 * 30) - 5;
	//	//box[15].y = (15 * 30);

	//	//box[2].x = (16 * 30) - 5;
	//	//box[2].y = (14 * 30) - 25;
	//};
}
