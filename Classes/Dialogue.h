#pragma once

#include <vector>
#include "Sentence.h"
#include "platform/CCPlatformMacros.h"

class Dialogue
{
public:
	Dialogue();
	~Dialogue();
	void addSentence(Sentence* sentence);
	Sentence* getSentence(int index);
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	std::vector<Sentence*> script;
};

