#include "IMode.h"
#include <cassert>

void IMode::ChangeType(const Type& type)
{
	// ���݂̏��
	current_ = type;

	// ���݂̏�Ԕԍ�
	currentIdx_ = static_cast<size_t>(current_);
}