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
			ATTR,OnLoad, OnUnload, OnAttack, OnInjured, OnRoundStart, OnRoundEnd,OnKilled
		};
		enum BuffType
		{
			Neutarl,Good,Bad
		};
		BuffBase();
		virtual ~BuffBase();
		virtual void apply(Character* target) = 0;
		virtual BuffBase* clone() = 0;
		virtual void init(std::vector<std::string>& buffMessage) = 0;
		void updateDuration();
		void setActive(bool a);
		bool isActive();

	protected:
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(TrigType, trigType, TrigType);
		CC_SYNTHESIZE(BuffType, buffType, BuffType);
		CC_SYNTHESIZE(int, priority, Priority);
		CC_SYNTHESIZE(int, duration, Duration);
		CC_SYNTHESIZE(std::string, id, ID);
		bool active;
	};
}
