#include "RandomDirectDamage.h"
#include "Dungeon.h"
#include "ToolFunction.h"



Skill::RandomDirectDamage::RandomDirectDamage()
{
}


Skill::RandomDirectDamage::~RandomDirectDamage()
{
}

Skill::RandomDirectDamage* Skill::RandomDirectDamage::createPrototype()
{
	return new RandomDirectDamage();
}

std::string Skill::RandomDirectDamage::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"对附近一个单位造成")
		+ ToolFunction::int2string(damage) + ToolFunction::WStr2UTF8(L"伤害");
}

void Skill::RandomDirectDamage::run()
{
	Character* target = searchTargetBFS(targetType);

	if (target)
	{
		target->sufferHPEffect(damage);
	}
}

void Skill::RandomDirectDamage::initExtraMessage(std::vector<std::string> extraMessage)
{
	damage = ToolFunction::string2int(extraMessage[0]);
	distance = ToolFunction::string2int(extraMessage[1]);


	switch (ToolFunction::string2int(extraMessage[2]))
	{
	case 0:
		targetType = Character::Good;
		break;
	case 1:
		targetType = Character::Neutral;
		break;
	case 2:
		targetType = Character::Bad;
		break;
	default:
		break;
	}

}

Character* Skill::RandomDirectDamage::searchTargetBFS(Character::Type type)
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point startPoint = caster->getMapCoord();
//	int searchDeep = caster->getViewSize();

	std::queue<cocos2d::Point> pointQueue;
	std::set<cocos2d::Point> discardPoint;

	pointQueue.push(startPoint);

	while (!pointQueue.empty())
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
					cocos2d::Point curCoord = curPoint;
					curCoord.x += i;
					curCoord.y += j;

					if (discardPoint.count(curCoord))
					{
						continue;
					}

					if (storey->isValid(curCoord)
						&& storey->getCharacter(curCoord)
						&& storey->getCharacter(curCoord)->getCharacterType() == type
						&& !storey->getCharacter(curCoord)->isDead())
					{
						return storey->getCharacter(curCoord);
					}
					else if (ToolFunction::getManhattanDistance(startPoint,curCoord)<distance)
					{
						pointQueue.push(curCoord);
						discardPoint.insert(curCoord);
					}
					else
					{
						discardPoint.insert(curCoord);
					}
				}
			}
		}
	}

	return nullptr;
}
