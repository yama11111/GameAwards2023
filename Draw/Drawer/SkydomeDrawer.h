#pragma once
#include "Model.h"

class SkydomeDrawerCommon
{

protected:
	
	// �ÓI���f��
	static YGame::Model* spModel_;

public:
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~SkydomeDrawerCommon() = default;

};

class SkydomeDrawer :
	public SkydomeDrawerCommon
{

private:
	
	// �I�u�W�F�N�g
	std::unique_ptr<YGame::ModelObject> obj_;
	
	// �F
	std::unique_ptr<YGame::Color> color_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^</param>
	/// <param name="scaleSize"> : �傫��</param>
	void Initialize(YMath::Matrix4* pParent, const float scaleSize);
	
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="scaleSize"> : �傫��</param>
	void Reset(const float scaleSize);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

};

