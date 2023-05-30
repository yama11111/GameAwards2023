#pragma once
#include "IDrawer.h"
#include <array>

// �S�[���`��p�R�����N���X
class GoalDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Core, // �j
		InsideCore, // ���g�j
		Inside, // ���g
		OutsideCore, // �O�g�j
		Outside, // �O�g
	};

protected:
	
	// �p�[�c�̑���
	static const size_t sPartsNum_ = 5;

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~GoalDrawerCommon() = default;
};

// �S�[���`��p�N���X
class GoalDrawer :
	private IDrawer,
	private GoalDrawerCommon
{

private:
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	
	// �����]�^�C�}�[
	YMath::Timer bindRotaTim_;

	// �����] (��) �C�[�W���O
	YMath::Ease<YMath::Vector3> inBindRotaEas_;
	
	// �����] (�O) �C�[�W���O
	YMath::Ease<YMath::Vector3> outBindRotaEas_;


	// �N���A���o
	bool isClear_ = false;
	
	// ���b�N�t���O
	bool isRock_ = false;


	// ���O�C���t���O
	bool isActLogin_ = false;

	// ���O�C���^�C�}�[
	YMath::Timer loginTim_;


	// �n�b�L���O��]�t���O
	bool isActHackRota_ = false;

	// �n�b�L���O��]�^�C�}�[
	YMath::Timer hackRotaTim_;

	// �n�b�L���O��] (��) �X�s�[�h
	YMath::Vector3 inHackRotaSpeed_;
	
	// �n�b�L���O��] (�O) �X�s�[�h
	YMath::Vector3 outHackRotaSpeed_;


	// �N���A��]�t���O
	bool isActClearRota_ = false;

	// �N���A��]�^�C�}�[
	YMath::Timer clearRotaTim_;

	// �N���A��] (��) �C�[�W���O
	YMath::Ease<YMath::Vector3> inClearRotaEas_;

	// �N���A��] (�O) �C�[�W���O
	YMath::Ease<YMath::Vector3> outClearRotaEas_;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="isRock"> : ���b�N���邩</param>
	void Initialize(YGame::Transform* pParent, const bool isRock);
	
	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="isRock"> : ���b�N���邩</param>
	void Reset(const bool isRock);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:

	///
	void Unlock();

	/// <summary>
	/// �N���A���o
	/// </summary>
	/// <param name="playerPos"> : �v���C���[�̈ʒu</param>
	void ActivateClearAnimation(const YMath::Vector3& playerPos);

private:

	// ���O�C���J�n
	void StartLogin(const YMath::Vector3& emitStartPos);
	
	// �n�b�L���O��]�J�n
	void StartHackRota();

	// �N���A��]�J�n
	void StartClearRota();
	
	// �����]�A�j���[�V����
	void BindRotaAnimation();

	// �N���A��]�A�j���[�V����
	void ClearAnimation();

};

