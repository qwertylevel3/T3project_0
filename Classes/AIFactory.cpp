#include "AIFactory.h"
#include "AICommonEnemy.h"
#include "VergilAI.h"



AIFactory::AIFactory()
{
}


AIFactory::~AIFactory()
{
}

AIBase* AIFactory::getAI(const std::string& AIName)
{
	if (AIName=="AICommonEnemy")
	{
		return new AICommonEnemy();
	}
	else if (AIName=="vergilAI")
	{
		return new VergilAI;
	}
}
