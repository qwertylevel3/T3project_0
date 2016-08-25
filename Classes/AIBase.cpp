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

Character* AIBase::searchTarget()
{
	Storey* storey=Dungeon::getInstance()->getStorey();
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	int searchDeep = characterPtr->getViewSize();

	std::queue<cocos2d::Point> pointQueue;
	pointQueue.push(startPoint);

	std::set<cocos2d::Point> discardPoint;

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

					if (storey->getCharacter(position))
					{
						if (storey->getCharacter(position) == characterPtr)
						{
							continue;
						}
						return storey->getCharacter(position);
					}
					else
					{
						pointQueue.push(position);
					}
				}
			}
		}
		searchDeep--;
	}

	return nullptr;
}
