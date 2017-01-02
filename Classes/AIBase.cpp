#include "AIBase.h"
#include "ExpHandler.h"
#include "Dungeon.h"
#include "Character.h"
#include "ToolFunction.h"
#include <queue>
#include "HudMessageBox.h"
#include <set>
#include "RandomNumber.h"

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
	Storey* storey = Dungeon::getInstance()->getStorey();
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	int searchDeep = characterPtr->getViewSize();

	std::queue<cocos2d::Point> pointQueue;
	std::set<cocos2d::Point> discardPoint;

	pointQueue.push(startPoint);

	while (!pointQueue.empty()
		&& searchDeep != 0)
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

					if (storey->isValid(position)
						&& storey->getCharacter(position)
						&& storey->getCharacter(position)->getCharacterType() == type
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

void AIBase::levelUp()
{
	ExpHandler* expHandler = characterPtr->getExphandler();

	while (expHandler->getCurAttrPoint() > 0)
	{
		int rn = RandomNumber::getInstance()->randomInt(1, 9);
		if (rn <= 3)
		{
			characterPtr->setStrength(
				characterPtr->getOriStrength() + 1
			);
		}
		else if (rn <= 6 && rn > 3)
		{
			characterPtr->setAgility(
				characterPtr->getOriAgility() + 1
			);
		}
		else
		{
			characterPtr->setIntellect(
				characterPtr->getOriIntellect() + 1
			);
		}
		expHandler->useAttrPoint();
	}
}

int AIBase::getManhattanDistance(Character* target)
{
	cocos2d::Point coordCaster = characterPtr->getMapCoord();
	cocos2d::Point coordTarget = target->getMapCoord();

	return abs(coordCaster.x - coordTarget.x) + abs(coordCaster.y - coordTarget.y);
}

void AIBase::seek(Character* target)
{
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = target->getMapCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	//todo
	if (nextStep == cocos2d::Point(-1, -1))
	{
		seek(endPoint);
		return;
	}

	if (nextStep == startPoint)
	{
		characterPtr->idle();
		return;
	}

	if (nextStep == endPoint)
	{
		if (startPoint.x > endPoint.x)
		{
			characterPtr->setOrientationLeft();
		}
		else if (startPoint.x < endPoint.x)
		{
			characterPtr->setOrientationRight();
		}
		if (startPoint.y > endPoint.y)
		{
			characterPtr->setOrientationUp();
		}
		else if (startPoint.y < endPoint.y)
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

void AIBase::seek(cocos2d::Point targetCoord)
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriCoord = characterPtr->getMapCoord();

	cocos2d::Point upCoord = cocos2d::Point(oriCoord.x, oriCoord.y - 1);
	cocos2d::Point downCoord = cocos2d::Point(oriCoord.x, oriCoord.y + 1);
	cocos2d::Point leftCoord = cocos2d::Point(oriCoord.x - 1, oriCoord.y);
	cocos2d::Point rightCoord = cocos2d::Point(oriCoord.x + 1, oriCoord.y);

	bool isMoveAbleUp = storey->isMoveAble(upCoord);
	bool isMoveAbleDown = storey->isMoveAble(downCoord);
	bool isMoveAbleLeft = storey->isMoveAble(leftCoord);
	bool isMoveAbleRight = storey->isMoveAble(rightCoord);

	if (targetCoord.x > oriCoord.x
		&& isMoveAbleRight)
	{
		characterPtr->moveRight();
		return;
	}
	else if (targetCoord.x < oriCoord.x
		&& isMoveAbleLeft)
	{
		characterPtr->moveLeft();
		return;
	}
	else if (targetCoord.y > oriCoord.y
		&& isMoveAbleDown)
	{
		characterPtr->moveDown();
		return;
	}
	else if (targetCoord.y < oriCoord.y
		&& isMoveAbleUp)
	{
		characterPtr->moveUp();
		return;
	}
	characterPtr->idle();
}

void AIBase::changeOrientationTo(Character* target)
{
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = target->getMapCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	if (startPoint.x > nextStep.x)
	{
		characterPtr->setOrientationLeft();
	}
	else if (startPoint.x < nextStep.x)
	{
		characterPtr->setOrientationRight();
	}
	if (startPoint.y > nextStep.y)
	{
		characterPtr->setOrientationUp();
	}
	else if (startPoint.y < nextStep.y)
	{
		characterPtr->setOrientationDown();
	}
	return;
}

bool AIBase::flee(Character* target)
{
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = target->getMapCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	if (nextStep.x == startPoint.x + 1
		&& nextStep.y == startPoint.y
		&& storey->isMoveAble(cocos2d::Point(startPoint.x - 1, startPoint.y)))
	{
		characterPtr->moveLeft();
		return true;
	}
	else if (nextStep.x == startPoint.x - 1
		&& nextStep.y == startPoint.y
		&& storey->isMoveAble(cocos2d::Point(startPoint.x + 1, startPoint.y)))
	{
		characterPtr->moveRight();
		return true;
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y - 1
		&& storey->isMoveAble(cocos2d::Point(startPoint.x, startPoint.y + 1)))
	{
		characterPtr->moveDown();
		return true;
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y + 1
		&& storey->isMoveAble(cocos2d::Point(startPoint.x, startPoint.y - 1)))
	{
		characterPtr->moveUp();
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool AIBase::isInAttackArea(Character* target)
{
	std::vector<cocos2d::Point> atkArea = characterPtr->getAtkArea();
	for each (cocos2d::Point point in atkArea)
	{
		if (target->getMapCoord() == point)
		{
			return true;
		}
	}
	return false;
}

bool AIBase::isNear(cocos2d::Point coord)
{
	cocos2d::Point characterCoord = characterPtr->getMapCoord();
	if (coord.x == characterCoord.x
		&& (coord.y == characterCoord.y + 1
			|| coord.y == characterCoord.y - 1
			|| coord.y == characterCoord.y))
	{
		return true;
	}
	else 	if (coord.y == characterCoord.y
		&& (coord.x == characterCoord.x + 1
			|| coord.x == characterCoord.x - 1
			|| coord.x == characterCoord.x))
	{
		return true;
	}
	return false;
}