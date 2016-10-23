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
			ATTR,OnLoad, OnUnload, OnAttack, OnInjured, OnRoundStart, OnRoundEnd
		};
		enum BuffType
		{
			Neutarl,Good,Bad
		};
		BuffBase();
		virtual ~BuffBase();
		virtual void apply(Character* target) = 0;
		void updateDuration();
		void setActive(bool a);
		bool isActive();

	protected:
		CC_SYNTHESIZE(std::string, name, Name);
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(TrigType, trigType, TrigType);
		CC_SYNTHESIZE(BuffType, buffType, BuffType);
		CC_SYNTHESIZE(int, priority, Priority);
		CC_SYNTHESIZE(int, duration, Duration);
		bool active;
	};
}
