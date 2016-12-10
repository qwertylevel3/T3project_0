#include "AIBase.h"
#include "Dungeon.h"
#include "Character.h"
#include "ToolFunction.h"
#include <queue>
#include "HudMessageBox.h"
#include <set>

using namespace Field;



AIBase::AIBase()
{
	characterPtr = nullptr;
}


AIBase::~AIBase()
{
}

void AIBase::update()
{
	characterPtr->idle();
}

void AIBase::feedback(Character* character)
{
	HudMessageBox::getInstance()->addMessage(L"对方不想和你说话");
}

void AIBase::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	
}

void AIBase::setCharacter(Character* character)
{
	characterPtr = character;
}

Character* AIBase::searchTargetBFS(Character::Type type)
{
	Storey* storey=Dungeon::getInstance()->getStorey();
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	int searchDeep = characterPtr->getViewSize();

	std::queue<cocos2d::Point> pointQueue;
	std::set<cocos2d::Point> discardPoint;

	pointQueue.push(startPoint);


	while (!pointQueue.empty() 
		&& searchDeep!=0)
	{
		cocos2d::Point curPoint = pointQueue.front();
		pointQueue.pop();
		discardPoint.insert(curPoint);

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((i == 0 || j == 0) && (i != j))
				{
					cocos2d::Point position = curPoint;
					position.x += i;
					position.y += j;

					if (discardPoint.count(position))
					{
						continue;
					}

					if (storey->getCharacter(position)
						&& storey->getCharacter(position)->getCharacterType()==type
						&& !storey->getCharacter(position)->isDead())
					{
						return storey->getCharacter(position);
					}
					else
					{
						pointQueue.push(position);
						discardPoint.insert(position);
					}
				}
			}
		}
		searchDeep--;
	}

	return nullptr;
}


void AIBase::seek(Character* target)
{
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

void AIBase::flee(Character* target)
{
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



bool AIBase::isInAttackArea(Character* target)
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

bool AIBase::isNear(cocos2d::Point coord)
{
	cocos2d::Point characterCoord = characterPtr->getMapCoord();
	if (coord.x==characterCoord.x
		&& (coord.y==characterCoord.y+1 
			|| coord.y==characterCoord.y-1
			|| coord.y==characterCoord.y))
	{
		return true;
	}
	else 	if (coord.y==characterCoord.y
		&& (coord.x==characterCoord.x+1 
			|| coord.x==characterCoord.x-1
			|| coord.x==characterCoord.x))
	{
		return true;
	}
	return false;
}

