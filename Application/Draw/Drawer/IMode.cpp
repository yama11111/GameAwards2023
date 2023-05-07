#include "IMode.h"
#include <cassert>

void IMode::ChangeType(const Type& type)
{
	// Œ»İ‚Ìó‘Ô
	current_ = type;

	// Œ»İ‚Ìó‘Ô”Ô†
	currentIdx_ = static_cast<size_t>(current_);
}