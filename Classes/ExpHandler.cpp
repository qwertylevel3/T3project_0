#include "ExpHandler.h"
#include "CharacterAttrHandler.h"
#include "Character.h"

const int ExpHandler::expRequire[27] =
{
	0,0,100,150,200,250,300,300,350,350,
	400,400,400,450,500,550,600,650,700,750,
	800,850,900,950,1000,1100,1200
};

const int ExpHandler::skillExpAdd = 40;

ExpHandler::ExpHandler(Character* character)
	:characterPtr(character)
{
	exp = 0;
	level = 1;
	attrPoint = 0;
}

ExpHandler::~ExpHandler()
{
}

void ExpHandler::addExp(const int e)
{
	exp += e;
	while (isLevelUp())
	{
		levelUp();
	}
}

void ExpHandler::useAttrPoint()
{
	attrPoint--;
}

int ExpHandler::getCurLevel()
{
	return level;
}

int ExpHandler::getCurExp()
{
	return exp;
}

int ExpHandler::getCurAttrPoint()
{
	return attrPoint;
}

int ExpHandler::getCurRequireExp()
{
	return expRequire[level + 1];
}

void ExpHandler::levelUp()
{
	exp = exp - expRequire[level + 1];
	level++;
	attrPoint++;

	CharacterAttrHandler* attrHandler = characterPtr->getAttrHandler();

	characterPtr->setMaxHP(attrHandler->getOriMaxHP() + 10);
	characterPtr->setMaxMP(attrHandler->getOriMaxMP() + 10);

	//TODO:
	//玩家的levelUp另外处理
//	if (characterPtr->getPlayType() != Character::Player)
//	{
		characterPtr->levelUp();
//	}
}

bool ExpHandler::isLevelUp()
{
	if (level >= 25)
	{
		return false;
	}
	if (exp >= expRequire[level + 1])
	{
		return true;
	}
	return false;
}