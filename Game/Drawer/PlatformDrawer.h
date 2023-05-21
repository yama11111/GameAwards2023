#pragma once
#include "IDrawer.h"
#include <array>

// ����`��p�R�����N���X
class PlatformDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eHologram, // �z���O����
		eLeft, // ��
		eRight, // �E
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// �z���O�����p�}�e���A��
	static std::unique_ptr<YGame::CBMaterial> sHologramMate_;

protected:

	// ----- ���� ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~PlatformDrawerCommon() = default;
};

// ����`��p�N���X
class PlatformDrawer :
	private IDrawer,
	private PlatformDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	void Initialize(YGame::Transform* pParent);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	void Reset();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:

	~PlatformDrawer() = default;
};
