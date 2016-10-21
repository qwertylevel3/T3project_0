#pragma once

#include<string>
#include "base/ccMacros.h"

class Character;

namespace Buff
{
	class BuffBase
	{
	public:
		enum TrigType
		{
			OnLoad, OnUnload, OnAttack, OnInjured, OnRoundStart, OnRoundOver
		};
		BuffBase();
		virtual ~BuffBase();
		virtual void apply(Character* target) = 0;
	protected:
		CC_SYNTHESIZE(std::string, name, Name);
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(TrigType, type, Type);
		CC_SYNTHESIZE(int, priority, Priority);
	};
}
