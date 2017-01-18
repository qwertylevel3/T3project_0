#include "RandomDirectDamage.h"
#include "RandomNumber.h"
#include "Dungeon.h"
#include "ToolFunction.h"
#include "EffectManager.h"

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
		+ ToolFunction::WStr2UTF8(L"对附近一个单位造成:(")
		+ ToolFunction::int2string(damagePre)
		+ ToolFunction::WStr2UTF8(L"% x [智力点数])")
		+ ToolFunction::WStr2UTF8(L"伤害");
}

void Skill::RandomDirectDamage::run()
{
	std::vector<Character*> allTarget=getTargetAround(targetType);
//	Character* target = searchTargetBFS(targetType);

	if (allTarget.empty())
	{
		return;
	}

	int roll = RandomNumber::getInstance()->randomInt(0, allTarget.size() - 1);

	Character* target = allTarget[roll];

	int damage = -double(damagePre)*double(caster->getIntellect()) / 100.0;

	if (target)
	{
		target->sufferHPEffect(damage);
		caster->addExp(-damage);
		EffectManager::getInstance()->showEffect("thunder", target->getPosition(), 0.2);
	}
}

void Skill::RandomDirectDamage::initExtraMessage(std::vector<std::string> extraMessage)
{
	damagePre = ToolFunction::string2int(extraMessage[0]);
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
					else if (ToolFunction::getManhattanDistance(startPoint, curCoord) < distance)
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

std::vector<Character*> Skill::RandomDirectDamage::getTargetAround(Character::Type type)
{
	int size = 3;
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	std::vector<Character* > allTarget;

	for (int i = -size; i <= size; i++)
	{
		for (int j = -size; j <= size; j++)
		{
			cocos2d::Point ori = caster->getMapCoord();

			Character* target = storey->getCharacter(ori.x+i, ori.y+j);

			if (target
				&& target->getCharacterType() == type
				&& !target->isDead())
			{
				allTarget.push_back(target);
			}
		}
	}
	return allTarget;
}