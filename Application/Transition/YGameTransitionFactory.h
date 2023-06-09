#pragma once
#include "ITransitionFactory.h"

namespace YScene
{
	class YGameTransitionFactory : public ITransitionFactory
	{
	
	public:
		
		// 暗転
		static const std::string Blackout_;
		
		// 埋め尽くすブロック
		static const std::string InfectionBlocks_;
	
	public:
		
		/// <summary> 
		/// シーン遷移生成
		/// </summary>
		/// <param name="transitionName"> : 遷移名</param>
		/// <returns>シーン遷移</returns>
		virtual BaseTransition* CreateTransition(const std::string& transitionName) override;
	};
}
