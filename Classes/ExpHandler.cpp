#include "ExpHandler.h"
#include "Character.h"

const int ExpHandler::expRequire[27] =
{
	0,0,100,100,100,150,150,150,200,200,
	200,250,250,250,300,300,300,400,400,400,
	500,500,500,600,600,800,800
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

void ExpHandler::levelUp()
{
	exp = exp - expRequire[level + 1];
	level++;
	attrPoint++;


	characterPtr->setMaxHP(characterPtr->getMaxHP() + 10);
	characterPtr->setMaxMP(characterPtr->getMaxMP() + 10);

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