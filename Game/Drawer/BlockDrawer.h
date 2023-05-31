#pragma once
#include "IDrawer.h"
#include <array>

// �u���b�N�`��p�R�����N���X
class BlockDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eCore, // �j
		eShell, // �k
		eEnd, // ���T�C�Y�p
	};

	// ���
	enum class Type
	{
		eBlack, // ��
		eWhite, // ��
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// ��ނ̑���
	static const size_t sTypeNum_ = static_cast<size_t>(Type::eEnd);

protected:

	// ----- �u���b�N ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<YGame::Model*, sPartsNum_>, sTypeNum_> spModels_;


public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~BlockDrawerCommon() = default;
};

// �u���b�N�`��p�N���X
class BlockDrawer :
	private IDrawer,
	private BlockDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// ���
	Type type_ = Type::eBlack;

	// ��ރC���f�b�N�X
	size_t typeIndex_ = 0;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="Type"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : ��</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : ��</param>
	void Initialize(YGame::Transform* pParent, const Type& type);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="Type"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : ��</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : ��</param>
	void Reset(const Type& type);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:

	~BlockDrawer() = default;
};

