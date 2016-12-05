#pragma once

#include "BuffBase.h"

namespace Buff
{
	class HPBuff:public BuffBase
	{
	public:
		HPBuff();
		~HPBuff();
		void apply(Character* target);
		HPBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, effectValue, EffectValue);
	};
}
