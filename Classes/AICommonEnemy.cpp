#include "AICommonEnemy.h"
#include "Character.h"
#include "ToolFunction.h"



AICommonEnemy::AICommonEnemy()
{
}

AICommonEnemy::~AICommonEnemy()
{
}

void AICommonEnemy::update()
{
	if (!characterPtr)
	{
		return;
	}
	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTarget();
	if (targetCharacter)
	{

		cocos2d::Point startPoint = characterPtr->getMapCoord();
		cocos2d::Point endPoint = targetCharacter->getMapCoord();
		cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

		if (nextStep == endPoint)
		{
			return;
		}

		if (nextStep.x == startPoint.x + 1
			&& nextStep.y == startPoint.y)
		{
			characterPtr->moveRight();
		}
		else if (nextStep.x == startPoint.x - 1
			&& nextStep.y == startPoint.y)
		{
			characterPtr->moveLeft();
		}
		else if (nextStep.x == startPoint.x
			&& nextStep.y == startPoint.y - 1)
		{
			characterPtr->moveUp();
		}
		else if (nextStep.x == startPoint.x
			&& nextStep.y == startPoint.y + 1)
		{
			characterPtr->moveDown();
		}
	}
}
