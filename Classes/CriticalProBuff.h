#pragma once

#include "BuffBase.h"

namespace Buff
{
	class CriticalProBuff:public BuffBase
	{
	public:
		CriticalProBuff();
		~CriticalProBuff();
		void apply(Character* target);
		CriticalProBuff * createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, criticalProOffset, CriticalProOffset);
	};
}
