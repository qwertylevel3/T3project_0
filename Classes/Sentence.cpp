#include "Sentence.h"


Sentence::Sentence()
{
	nextIndex = 0;
}


Sentence::~Sentence()
{
}

int Sentence::next()
{
	return nextIndex;
}
