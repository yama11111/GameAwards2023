#pragma once
#include "Effect.h"

namespace YGame
{
	class EffectManager
	{
	private:
		std::list<std::unique_ptr<IEffect>> particles_;
	public:
		void Initialize();
		void Update();
		void Draw();
	};
}

