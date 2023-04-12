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
public:
	virtual ~BlockDrawerCommon() = default;
};

// �u���b�N�`��p�N���X
class BlockDrawer :
	private IDrawer, 
	private BlockDrawerCommon
{
private:
	// ----- �I�u�W�F�N�g ----- // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// �F
	std::unique_ptr<YGame::Color> color_;

	// �ۑ��p
	Mode save_ = Mode::None;

	// ----- �A�j���[�V����	 ----- //

	// �t�F�[�h�C������
	bool isFadeIn_ = false;
	// �t�F�[�h�C���p�^�C�}�[
	YMath::Timer fadeInTim_;
	// �t�F�[�h�C���p�F�C�[�W���O
	YMath::Ease<YMath::Vector4> fadeInColorEas_;
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Initialize(YGame::Transform* pParent, const Mode& mode);
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
	// �`��
	void Draw();
public:
	// ������o���A�j���[�V����
	void FadeInAnimation(const unsigned int frame);
private:
	// �A�j���[�V�������Z�b�g
	void ResetAnimation();
	// �������[�V����
	void IdleAnimation() override;
public:
	~BlockDrawer() = default;
};

