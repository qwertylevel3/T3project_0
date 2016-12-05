#pragma once

#include "BuffBase.h"

namespace Buff
{
	class MPBuff:public BuffBase
	{
	public:
		MPBuff();
		~MPBuff();
		void apply(Character* target);
		MPBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, effectValue, EffectValue);
	};
}
