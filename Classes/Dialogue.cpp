#include "Dialogue.h"
#include "base\ccMacros.h"


Dialogue::Dialogue()
{
}


Dialogue::~Dialogue()
{
}

void Dialogue::addSentence(Sentence* sentence)
{
	script.push_back(sentence);
}

Sentence* Dialogue::getSentence(int index)
{
	CCAssert(index >= 0 && index < script.size(), "index is out of script size");
	return script.at(index);
}
