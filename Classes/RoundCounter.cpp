#include "RoundCounter.h"



RoundCounter::RoundCounter()
{
	roundCount = 0;
}


RoundCounter::~RoundCounter()
{
}

void RoundCounter::nextRound()
{
	roundCount++;
}
