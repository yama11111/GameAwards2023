#pragma once
#include "ParticleManager.h"
#include "SkydomeDrawer.h"
#include "TowerDrawer.h"

class BackgroundDrawerCommon
{

protected:

	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YGame::ParticleManager* spParticleMan_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pParticleMan"> : �p�[�e�B�N���}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(YGame::ParticleManager* pParticleMan);

public:

	virtual ~BackgroundDrawerCommon() = default;

};

class BackgroundDrawer :
	private BackgroundDrawerCommon
{

private:

	// �^���[
	struct Tower
	{
		// �e�g�����X�t�H�[��
		YGame::Transform transform_;

		// �`��N���X
		TowerDrawer drawer_;
	};

private:

	// �^���[���X�g
	std::list<std::unique_ptr<Tower>> towers_;

	// �X�J�C�h�[��
	YGame::Transform skydome_;

	// �X�J�C�h�[���`��N���X
	SkydomeDrawer skydomeDra_;


	// �A�O���b�h�����p�^�C�}�[
	YMath::Timer emitBubbleGridTim_;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���Z�b�g
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

	/// <summary>
	/// �^���[������
	/// </summary>
	void InitializeTowers();

	/// <summary>
	/// �G�~�b�^�[�X�V
	/// </summary>
	void UpdateEmitter();

	/// <summary>
	/// �A�O���b�h����
	/// </summary>
	void EmitBubbleGrid();
};

