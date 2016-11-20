#include "AICommonEnemy.h"
#include "Character.h"
#include "ToolFunction.h"
#include "Player.h"



AICommonEnemy::AICommonEnemy()
{
	deadLine = 20;
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
	Character* targetCharacter = searchTargetBFS();
	if (targetCharacter)
	{
		if (isDangerous())
		{
			flee(targetCharacter);
		}
		else
		{
			if (!isInAttackArea(targetCharacter))
			{
				seek(targetCharacter);
			}
			else
			{
				characterPtr->runSkill("attack");
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}

void AICommonEnemy::seek(Character* target)
{
	CCAssert(target == Player::getInstance()->getcharacterPtr(), "target is not player");

	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = target->getMapCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	if (nextStep == endPoint)
	{
		if (startPoint.x>endPoint.x)
		{
			characterPtr->setOrientationLeft();
		}
		else if (startPoint.x<endPoint.x)
		{
			characterPtr->setOrientationRight();
		}
		if (startPoint.y>endPoint.y)
		{
			characterPtr->setOrientationUp();
		}
		else if(startPoint.y<endPoint.y)
		{
			characterPtr->setOrientationDown();
		}
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

void AICommonEnemy::flee(Character* target)
{
	CCAssert(target == Player::getInstance()->getcharacterPtr(), "target is not player");

	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = target->getMapCoord();
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

bool AICommonEnemy::isInAttackArea(Character* target)
{
	std::vector<cocos2d::Point> atkArea = characterPtr->getAtkArea();
	for each (cocos2d::Point point in atkArea)
	{
		if (target->getMapCoord()==point)
		{
			return true;
		}
	}
	return false;
}
