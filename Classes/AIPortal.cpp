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

bool AIPortal::isPlayerNear()
{
	cocos2d::Point oriCoord = characterPtr->getMapCoord();
	cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();

	if (ToolFunction::isNear8(oriCoord,playerCoord))
	{
		return true;
	}
	return false;
}
