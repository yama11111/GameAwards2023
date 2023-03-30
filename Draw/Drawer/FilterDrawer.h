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
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// �t�B���^�[�`��p�N���X
class FilterDrawer :
	private IDrawer,
	private FilterDrawerCommon
{
private:
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	void Initialize(YMath::Matrix4* pParent);
	// ���Z�b�g (���g����������)
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
private:
	// �������[�V����
	void IdleAnimation() override;
public:
	~FilterDrawer() = default;
};


