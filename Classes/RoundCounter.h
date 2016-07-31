#pragma once

#include"HudSender.h"
#include"Singleton.h"
#include"platform\CCPlatformMacros.h"

class RoundCounter:public HudSender,public Singleton<RoundCounter>
{
public:
	RoundCounter();
	~RoundCounter();
	void nextRound();
	void updateSender();
	std::string getMessage();
protected:
	CC_SYNTHESIZE(int, roundCount, RoundCount);
};

