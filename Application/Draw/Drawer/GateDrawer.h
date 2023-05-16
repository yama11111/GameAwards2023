#pragma once
#include "IDrawer.h"
#include <array>

// �Q�[�g�`��p�R�����N���X
class GateDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Inside, // ���g
		InsideLight, // ���g (��)
		Outside, // �O�g
		OutsideLight, // �O�g (��)
	};

protected:
	
	// �p�[�c�̑���
	static const size_t PartsNum_ = 4;

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, PartsNum_> spModels_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~GateDrawerCommon() = default;
};

// �Q�[�g�`��p�N���X
class GateDrawer :
	private IDrawer,
	private GateDrawerCommon
{

private:
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, PartsNum_> modelObjs_;

	// �F (����, ��, ����)
	std::unique_ptr<YGame::CBColor> color_;

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
	
	// �X�V
	void Update();
	
	// �`��
	void Draw();

private:
	
	// �������[�V����
	void IdleAnimation() override;

public:
	
	~GateDrawer() = default;
};

