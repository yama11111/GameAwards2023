#pragma once

// ��ԃN���X
class IMode
{

public:

	// �^�C�v
	enum class Type
	{
		Normal	 = 0, // �ʏ�
		Movable  = 1, // ��
	};

	// ��Ԃ̐�
	static const size_t sTypeNum_ = 2;

	// �ʏ�C���f�b�N�X
	static const size_t sNormalIdx = static_cast<size_t>(IMode::Type::Normal);
	
	// ���C���f�b�N�X
	static const size_t sMovableIdx = static_cast<size_t>(IMode::Type::Movable);

private:

	// ���݂̃^�C�v
	Type current_ = Type::Normal;

	// ���݂̃^�C�v�ԍ�
	size_t currentIdx_ = sNormalIdx;

protected:

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="modeType"> : �^�C�v</param>
	void ChangeType(const Type& type);

protected:

	/// <summary>
	/// ���݂̃^�C�v�ԍ��擾
	/// </summary>
	/// <returns>���݂̏�Ԕԍ�</returns>
	size_t CurrentTypeIndex() { return currentIdx_; }

	/// <summary>
	/// ���݂̃^�C�v�擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	Type CurrentType() { return current_; }
};