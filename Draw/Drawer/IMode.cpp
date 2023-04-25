#include "IMode.h"
#include <cassert>

void IMode::ChangeType(const Type& type)
{
	// 現在の状態
	current_ = type;

	// 現在の状態番号
	currentIdx_ = static_cast<size_t>(current_);
}