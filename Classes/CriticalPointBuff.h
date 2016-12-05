#pragma once

#include "BuffBase.h"

namespace Buff
{
	class CriticalPointBuff:public BuffBase
	{
	public:
		CriticalPointBuff();
		~CriticalPointBuff();
		void apply(Character* target);
		CriticalPointBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, criticalPointOffset, CriticalPointOffset);
	};
}
