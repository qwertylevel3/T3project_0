#pragma once

#include <string>
#include "platform/CCPlatformMacros.h"

class Sentence
{
public:
	Sentence();
	virtual ~Sentence();
	virtual int run()=0;
protected:
	CC_SYNTHESIZE(std::string, actorSpriteName, ActorSpriteName);
	CC_SYNTHESIZE(std::string, word, Word);
};

