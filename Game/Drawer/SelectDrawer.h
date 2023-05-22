#pragma once
#include "StageDrawer.h"
#include "CardDrawer.h"
#include "LetterBoxDrawer.h"
#include "SkydomeDrawer.h"
#include "Sprite2D.h"
#include "Power.h"
#include "StageConfig.h"
#include "ParticleManager.h"

class SelectDrawerCommon
{

protected:
	
	// �ÓI�n�����f��
	static YGame::Model* spEarthModel_;
	
	// �ÓI���S�X�v���C�g
	static YGame::Sprite2D* spLogoSpr_;
	
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
	
	// �X�e�[�W�ݒ�|�C���^
	static StageConfig* spStageConfig_;

	// �^���[�p�}�e���A��
	static std::unique_ptr<YGame::CBMaterial> sTowerMate_;

	// �^���[�p���C�g
	static std::unique_ptr<YGame::CBLightGroup> sTowerLight_;
	
	// �n���p�}�e���A��
	static std::unique_ptr<YGame::CBMaterial> sEarthMate_;

	// �n���p���C�g
	static std::unique_ptr<YGame::CBLightGroup> sEarthLight_;

	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YGame::ParticleManager* spParticleMan_;

public:
	
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~SelectDrawerCommon() = default;

};

class SelectDrawer : private SelectDrawerCommon
{

private:
	
	// ----- �I�u�W�F�N�g ----- //
	
	// �j
	std::unique_ptr<YGame::Transform> core_;
	
	
	// �n�����f���I�u�W�F�N�g
	std::unique_ptr<YGame::Model::Object> earthObj_;
	
	// �F
	std::unique_ptr<YGame::CBColor> color_;

	
	// �X�e�[�W�g�����X�t�H�[�� (�g���p)
	std::array<std::unique_ptr<YGame::Transform>, 24> aliveStages_;
	
	// �X�e�[�W�g�����X�t�H�[�� (�g��Ȃ��p)
	std::unique_ptr<YGame::Transform> deadStage_;
	
	// �X�e�[�W�`��N���X
	std::vector<std::unique_ptr<StageDrawer>> stageDras_;


	// �X�e�[�W�J�[�h�p�g�����X�t�H�[�� (�e)
	std::vector<std::unique_ptr<YGame::Transform>> cards_;
	
	// �X�e�[�W�J�[�h�`��N���X
	std::vector<std::unique_ptr<CardDrawer>> cardDras_;

	
	// ���^�[�{�b�N�X
	std::unique_ptr<YGame::LetterBoxDrawer> lbDra_;


	// ���S�X�v���C�g�I�u�W�F�N�g
	std::unique_ptr<YGame::Sprite2D::Object> logoObj_;


	// �V��
	std::unique_ptr<YGame::Transform> skydome_;

	// �V���`��N���X
	SkydomeDrawer skydomeDra_;


	// ----- �A�j���[�V���� ----- //

	// ���쒆��
	bool isAct_ = false;
	
	
	// �J�n����]�p�C�[�W���O
	YMath::Ease<float> startRotaEas_;
	
	// �J�n����]�p�^�C�}�[
	YMath::Timer startRotaTim_;
	
	
	// �X�e�[�W��]�p�C�[�W���O
	YMath::Ease<float> stageRotaEas_;
	
	// �X�e�[�W��]�p�p���[
	std::vector<YMath::Power> stageRotaPows_;


	// �A�O���b�h�����p�^�C�}�[
	YMath::Timer emitBubbleGridTim_;

public:
	
	// ������
	void Initialize();
	
	// ���Z�b�g
	void Reset();
	
	// �X�V
	void Update();
	
	// �`��
	void Draw();

public:
	
	// ����ݒ�
	void SetActive(const bool isAct) { isAct_ = isAct; }

private:
	
	// �A�j���[�V�����̉�]�X�V
	void UpdateRotaAnimation();

	/// <summary>
	/// �G�~�b�^�[�X�V
	/// </summary>
	void UpdateEmitter();

	/// <summary>
	/// �A��������
	/// </summary>
	void EmitBubbleCharacter();
};
