#include "AIFactory.h"
#include "AIPlayer.h"
#include "AIPersephone.h"
#include "AICommonEnemy.h"
#include "AIDestroyWizard.h"
#include "AIVergil.h"
#include "AIShrine.h"
#include "AIStatue.h"
#include "AIPortal.h"
#include "AISnack.h"
#include "AIEnts.h"
#include "AICentaur.h"
#include "AITauren.h"
#include "AIVampire.h"
#include "AISummonWizard.h"
#include "AICommonFriend.h"
#include "AISuccubus.h"
#include "AIBlackSnack.h"



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
	else if (AIName == "AICentaur")
	{
		return new AICentaur();
	}
	else if (AIName == "AITauren")
	{
		return new AITauren();
	}
	else if (AIName == "AIVampire")
	{
		return new AIVampire();
	}
	else if (AIName == "AISummonWizard")
	{
		return new AISummonWizard();
	}
	else if (AIName == "AIBlackSnack")
	{
		return new AIBlackSnack();
	}
	else if (AIName == "AICommonFriend")
	{
		return new AICommonFriend();
	}
	else if (AIName == "AISuccubus")
	{
		return new AISuccubus();
	}
	else if (AIName=="AIDestroyWizard")
	{
		return new AIDestroyWizard();
	}
	else if (AIName=="AIPersephone")
	{
		return new AIPersephone();
	}
	else if (AIName == "AIPlayer")
	{
		return new AIPlayer();
	}
	else
	{
		return nullptr;
	}
}
