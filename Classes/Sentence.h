#pragma once

#include <string>
#include "platform/CCPlatformMacros.h"

class Sentence
{
public:
	Sentence();
	virtual ~Sentence();
	int next();
	virtual void run() = 0;
protected:
	CC_SYNTHESIZE(int, nextIndex, NextIndex);
	CC_SYNTHESIZE(std::string, actorSpriteName, ActorSpriteName);
	CC_SYNTHESIZE(std::string, word, Word);
};

