#pragma once
#include "IDrawer.h"
#include <array>

// �t�B���^�[�`��p�R�����N���X
class FilterDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Monitor, // ���j�^�[
	};

protected:
	
	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, PartsNum_> spModels_;

public:
	
	// �ÓI������
	static void StaticInitialize();

public:
	
	virtual ~FilterDrawerCommon() = default;
};

// �t�B���^�[�`��p�N���X
class FilterDrawer :
	private IDrawer,
	private FilterDrawerCommon
{

private:
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// �F
	std::unique_ptr<YGame::Color> color_;

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

private:
	
	// �������[�V����
	void IdleAnimation() override;

public:
	
	~FilterDrawer() = default;
};


