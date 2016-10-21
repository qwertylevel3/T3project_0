#pragma once

#include<string>
#include "base/ccMacros.h"

class Character;

class BuffBase
{
public:
	enum TrigType
	{
		OnLoad,OnUnload,OnAttack,OnInjured,OnRoundStart,OnRoundOver
	};
	BuffBase();
	virtual ~BuffBase();
	virtual void apply(Character* target)=0;
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(TrigType, type, Type);
};
