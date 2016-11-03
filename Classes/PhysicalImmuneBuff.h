#pragma once

#include "BuffBase.h"

namespace Buff
{
	class PhysicalImmuneBuff:public BuffBase
	{
	public:
		PhysicalImmuneBuff();
		~PhysicalImmuneBuff();
		void apply(Character* target);
		PhysicalImmuneBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
	};
}
