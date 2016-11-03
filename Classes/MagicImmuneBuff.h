#pragma once

#include "BuffBase.h"

namespace Buff
{
	class MagicImmuneBuff:public BuffBase
	{
	public:
		MagicImmuneBuff();
		~MagicImmuneBuff();
		void apply(Character* target);
		MagicImmuneBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
	};
}
