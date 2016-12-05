#pragma once

#include "BuffBase.h"

namespace Buff
{
	class ComboBuff :public BuffBase
	{
	public:
		ComboBuff();
		~ComboBuff();
		void apply(Character* target);
		ComboBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, comboOffset, ComboOffset);
	};
}
