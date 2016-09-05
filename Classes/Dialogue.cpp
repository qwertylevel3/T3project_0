#include "Dialogue.h"
#include "base\ccMacros.h"


Dialogue::Dialogue()
{
}


Dialogue::~Dialogue()
{
}

int Dialogue::run()
{
	CCAssert(!script.empty(), "dialogue is empty");

	int nextIndex = script[0]->run();
	while (nextIndex >= 0)
	{
		nextIndex = script[nextIndex]->run();
	}
	return nextIndex;
}

void Dialogue::addSentence(Sentence* sentence)
{
	script.push_back(sentence);
}
