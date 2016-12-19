#include "AIFactory.h"
#include "AICommonEnemy.h"
#include "AIVergil.h"
#include "AIShrine.h"
#include "AIStatue.h"
#include "AIPortal.h"
#include "AISnack.h"
#include "AIEnts.h"



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
	else if (AIName=="AIVergil")
	{
		return new AIVergil;
	}
	else if (AIName == "AIShrine")
	{
		return new AIShrine;
	}
	else if (AIName == "AIStatue")
	{
		return new AIStatue;
	}
	else if (AIName == "AIPortal")
	{
		return new AIPortal;
	}
	else if (AIName == "AISnack")
	{
		return new AISnack();
	}
	else if (AIName == "AIEnts")
	{
		return new AIEnts();
	}
	else
	{
		return nullptr;
	}
}
