#pragma once
#include "IDrawer.h"
#include <array>

// �^���[�`��p�R�����N���X
class TowerDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		eCore, // �j
		eShell, // �k
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
	static const size_t sPartsNum_ = 2;

	// ��ނ̑���
	static const size_t sTypeNum_ = static_cast<size_t>(Type::eEnd);

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<YGame::Model*, sPartsNum_>, sTypeNum_> spModels_;
	
	// �}�e���A���|�C���^
	static YGame::CBMaterial* spUniqueMate_;

	// ���C�g�|�C���^
	static YGame::CBLightGroup* spUniqueLight_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pMate"> : �}�e���A���|�C���^</param>
	/// <param name="pLight"> : ���C�g�|�C���^</param>
	static void StaticInitialize(
		YGame::CBMaterial* pMate,
		YGame::CBLightGroup* pLight);

public:
	
	virtual ~TowerDrawerCommon() = default;

};

// �^���[�`��p�N���X
class TowerDrawer :
	private IDrawer,
	private TowerDrawerCommon
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
	void Draw(const YGame::DrawLocation& location);

public:

	~TowerDrawer() = default;

};

