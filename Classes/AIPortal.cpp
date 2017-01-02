#include "AIPortal.h"
#include "Player.h"
#include "ToolFunction.h"
#include "GameController.h"
#include "SplashLayer.h"



AIPortal::AIPortal()
{
}


AIPortal::~AIPortal()
{
}

void AIPortal::update()
{
	if (isPlayerNear())
	{
		characterPtr->speak(L"按'E'进入下一层");
		characterPtr->idle();
	}
	else
	{
		characterPtr->idle();
	}
}

void AIPortal::feedback(Character* character)
{
//	GameController::getInstance()->startMission(1);
	GameController::getInstance()->nextMission();
}
