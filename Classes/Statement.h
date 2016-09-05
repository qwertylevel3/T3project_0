#pragma once
#include "Sentence.h"
#include "platform/CCPlatformMacros.h"

class Statement :
	public Sentence
{
public:
	Statement();
	~Statement();
	int run();
protected:
	CC_SYNTHESIZE(int, next, Next);
};

