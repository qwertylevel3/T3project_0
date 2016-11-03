#pragma once

#include "BuffBase.h"

namespace Buff
{
	class EvadeBuff:public BuffBase
	{
	public:
		EvadeBuff();
		~EvadeBuff();
		void apply(Character* target);
		EvadeBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, evadeOffset, EvadeOffset);
	};
}
