#pragma once
#include "Model.h"

class SkydomeDrawerCommon
{

protected:
	
	// �ÓI���f��
	static YGame::Model* spModel_;

	// �ÓI�F�|�C���^
	static YGame::Color* spColor_;

public:
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pColor"> : �F�|�C���^</param>
	static void StaticInitialize(YGame::Color* pColor);

public:
	
	virtual ~SkydomeDrawerCommon() = default;

};

class SkydomeDrawer :
	public SkydomeDrawerCommon
{

private:
	
	// �I�u�W�F�N�g
	std::unique_ptr<YGame::Model::Object> obj_;

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

