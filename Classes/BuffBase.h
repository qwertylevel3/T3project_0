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
			NeverTrig,ATTR,OnLoad, OnUnload, OnAttack, OnInjured, OnRoundStart, OnRoundEnd,OnKilled
		};
		enum BuffType
		{
			Neutarl,Good,Bad
		};
		BuffBase();
		virtual ~BuffBase();
		virtual void apply(Character* target) = 0;
		virtual BuffBase* createPrototype() = 0;
		virtual std::string getDescription();

		void init(std::vector<std::string> buffMessage);
		void updateDuration();
		void setActive(bool a);
		bool isActive();

		std::string getDurationDescriptionStr();
	protected:
		void initBaseMessage(std::vector<std::string> baseMessage);
		virtual void initExtraMessage(std::vector<std::string> baseMessage)=0;

		void initCname(std::string cnameStr);
		void initTrigType(const std::string& trigTypeStr);
		void initBuffType(const std::string& buffTypeStr);
		void initPriority(const std::string& priorityStr);
		void initDuration(const std::string& durationStr);

		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(TrigType, trigType, TrigType);
		CC_SYNTHESIZE(BuffType, buffType, BuffType);
		CC_SYNTHESIZE(int, priority, Priority);
		CC_SYNTHESIZE(int, duration, Duration);
		CC_SYNTHESIZE(std::string, id, ID);
		bool active;
	};
}
