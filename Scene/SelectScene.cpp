#include "SelectScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include "StageConfig.h"
#include <cassert>

#pragma region ���O��Ԑ錾
using YScene::SelectScene;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void SelectScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	LetterBoxDrawerCommon::StaticInitialize();
	SkydomeDrawerCommon::StaticInitialize();
	StageDrawerCommon::StaticInitialize(&transferVP_);
	SelectDrawerCommon::StaticInitialize(&transferVP_);
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	// �X�e�[�W�ԍ�
	stageIdx_ = 1;

	// �`��p�N���X������
	dra_.Initalize(&stageIdx_);
	dra_.SetActive(true);

	// �V��������
	skydome_.Initialize();

	// ���^�[�{�b�N�X������
	lbDra_.Initialize(96.0f, 96.0f);

	// �J����������
	camera_.Initialize({ {+4.0f,+31.0f,-15.0f}, {-PI / 15.0f,-PI / 30.0f,-PI / 45.0f} });
	//camera_.Initialize({ {0,0,-100}, {} });

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});
}
#pragma endregion

#pragma region �I������
void SelectScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void SelectScene::Update()
{
	// �X�e�[�W�I�� (A or D)
	stageIdx_ += sKeys_->IsTrigger(DIK_D) - sKeys_->IsTrigger(DIK_A);

	// �X�e�[�W�ԍ��N�����v
	stageIdx_ = YMath::Clamp(stageIdx_, 1, StageNum);


	// ���̃V�[���� (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		SceneManager::GetInstance()->Change("PLAY", "INFECTION");
	}


	// �`��p�N���X�X�V
	dra_.Update();

	// �V���X�V
	skydome_.Update();

	// ���^�[�{�b�N�X�X�V
	lbDra_.Update();

	// �J�����X�V + ���
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
}
#pragma endregion


#pragma region �`��
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{
	// �V���`��
	skydome_.Draw();

	// �`��p�N���X�X�V
	dra_.DrawModel();
}

void SelectScene::DrawSprite3Ds()
{
	// �`��p�N���X�X�V
	dra_.DrawSprite3D();
}

void SelectScene::DrawFrontSprite2Ds()
{
	// ���^�[�{�b�N�X�`��
	lbDra_.Draw();

	// �`��p�N���X�X�V
	dra_.DrawSprite2D();
}

void SelectScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion