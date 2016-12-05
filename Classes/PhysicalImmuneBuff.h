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
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
	};
}
