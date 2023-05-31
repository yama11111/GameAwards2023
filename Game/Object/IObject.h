#pragma once
#include "ObjectCollider.h"
#include "Transform.h"
#include "Audio.h"
#include <memory>

class Stage;

class IObject :
	public ObjectCollider
{

protected:

	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;

	// 1F�O�̍���
	YMath::Vector3 elderLeftTop_;

public:

	/// <summary>
	/// ����X�V
	/// </summary>
	void UpdateLeftTop();

	/// <summary>
	/// ����O�X�V
	/// </summary>
	virtual void PreUpdate() = 0;
	
	/// <summary>
	/// �����X�V
	/// </summary>
	virtual void PostUpdate() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

public:

	void StopWarpSE() { spWarpSE_->Stop(); }
	void PlayWarpSE() { spWarpSE_->Play(false); }

public:

	virtual ~IObject() = default;

protected:

	// �ÓI�X�e�[�W�}�l�[�W���[�|�C���^
	static Stage* spStageMan_;

	static YGame::Audio* spWarpSE_;

public:
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pStageMan"> : �X�e�[�W�}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(Stage* pStageMan);

};

