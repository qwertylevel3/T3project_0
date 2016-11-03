#pragma once

#include "BuffBase.h"

namespace Buff
{
	class CriticalPerBuff:public BuffBase
	{
	public:
		CriticalPerBuff();
		~CriticalPerBuff();
		void apply(Character* target);
		CriticalPerBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, criticalPerOffset, CriticalPerOffset);
	};
}
