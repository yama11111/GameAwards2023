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
		Spring	 = 2, // �΂�
		Junction1 = 3, // ��
		Junction2 = 4, // ��
		Clear = 5, // �N���A
		End, // ���T�C�Y�p
	};

	// ��Ԃ̐�
	static const size_t sTypeNum_	 = static_cast<size_t>(IMode::Type::End);

	// �ʏ�C���f�b�N�X
	static const size_t sNormalIdx	 = static_cast<size_t>(IMode::Type::Normal);
	
	// ���C���f�b�N�X
	static const size_t sMovableIdx	 = static_cast<size_t>(IMode::Type::Movable);

	// �΂˃C���f�b�N�X
	static const size_t sSpringIdx	 = static_cast<size_t>(IMode::Type::Spring);

	// �ڍ��C���f�b�N�X
	static const size_t sJunction1Idx = static_cast<size_t>(IMode::Type::Junction1);
	static const size_t sJunction2Idx = static_cast<size_t>(IMode::Type::Junction2);
	static const size_t sClearIdx = static_cast<size_t>(IMode::Type::Clear);

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