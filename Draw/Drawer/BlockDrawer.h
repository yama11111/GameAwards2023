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
		Cube, // ������
	};
protected:
	// ���[�h�̑���
	static const size_t ModeNum_ = 3;
	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;
protected:
	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<std::unique_ptr<YGame::Model>, PartsNum_>, ModeNum_> sModels_;
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// �u���b�N�`��p�N���X
class BlockDrawer :
	private IDrawer, 
	private BlockDrawerCommon
{
private:
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_>, ModeNum_> modelObjs_;

	// �����F
	std::unique_ptr<YGame::Color> invisibleColor_;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Initialize(YMath::Matrix4* pParent, const Mode& mode);
	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Reset(const Mode& mode);
	// �X�V
	void Update();
	// �O���`�� (�t�B���^�[��� �� �ɌĂ�)
	void PreDraw();
	// ����`�� (�t�B���^�[��� �� �ɌĂ�)
	void PostDraw();
public:
	// �������[�V����
	void IdleAnimation();
};

