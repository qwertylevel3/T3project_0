#include "AIBase.h"
#include "Dungeon.h"
#include "Character.h"
#include <queue>
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

}

void AIBase::setCharacter(Character* character)
{
	characterPtr = character;
}

Character* AIBase::searchTargetBFS()
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
						&& storey->getCharacter(position)->getCharacterType()==Character::Good)
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
