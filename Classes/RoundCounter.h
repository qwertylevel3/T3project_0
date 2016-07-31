#pragma once

#include"Singleton.h"
#include"platform\CCPlatformMacros.h"

class RoundCounter:public Singleton<RoundCounter>
{
public:
	RoundCounter();
	~RoundCounter();
	void nextRound();
protected:
	CC_SYNTHESIZE(int, roundCount, RoundCount);
};

