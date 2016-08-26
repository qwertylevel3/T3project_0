#include "AICommonEnemy.h"
#include "Character.h"
#include "ToolFunction.h"
#include "Player.h"



AICommonEnemy::AICommonEnemy()
{
	deadLine = 50;
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
		if (isDangerous())
		{
			flee(targetCharacter);
		}
		else
		{
			seek(targetCharacter);
		}
	}
}

void AICommonEnemy::seek(Character* character)
{
	CCAssert(character == Player::getInstance()->getcharacterPtr(), "target is not player");

	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = character->getMapCoord();
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
	else
	{
		CCAssert(false, "error nextStep");
	}
}

void AICommonEnemy::flee(Character* character)
{
	CCAssert(character == Player::getInstance()->getcharacterPtr(), "target is not player");

	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = character->getMapCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	if (nextStep.x == startPoint.x + 1
		&& nextStep.y == startPoint.y)
	{
		characterPtr->moveLeft();
	}
	else if (nextStep.x == startPoint.x - 1
		&& nextStep.y == startPoint.y)
	{
		characterPtr->moveRight();
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y - 1)
	{
		characterPtr->moveDown();
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y + 1)
	{
		characterPtr->moveUp();
	}
	else
	{
		CCAssert(false, "error nextStep");
	}

}

bool AICommonEnemy::isDangerous()
{
	double HP = characterPtr->getHP();
	double maxHP = characterPtr->getMaxHP();
	if (HP * 100 / maxHP < deadLine)
	{
		return true;
	}
	return false;
}
