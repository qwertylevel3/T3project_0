#pragma once

#include <vector>
#include "Sentence.h"
#include "platform/CCPlatformMacros.h"

class Dialogue
{
public:
	Dialogue();
	~Dialogue();
	int run();
	void addSentence(Sentence* sentence);
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	std::vector<Sentence*> script;
};

