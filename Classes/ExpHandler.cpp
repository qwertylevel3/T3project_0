#include "ExpHandler.h"
#include "Character.h"

const int ExpHandler::expRequire[27] =
{
	0,0,100,100,100,150,150,150,200,200,
	200,250,250,250,300,300,300,400,400,400,
	500,500,500,600,600,800,800
};

const int ExpHandler::atkExpAdd[3] = {5,5,0};
const int ExpHandler::evadeExpAdd[3] = {0,5,0};
const int ExpHandler::criticalExpAdd[3]={5,2,0};
const int ExpHandler::blockExpAdd[3] = {5,2,0};
const int ExpHandler::comboExpAdd[3] = {2,5,0};
const int ExpHandler::sphereExpAdd[3] = {0,0,2};
const int ExpHandler::skillExpAdd[3] = {0,0,10};

ExpHandler::ExpHandler(Character* character)
	:characterPtr(character)
{
	for (int i = 0; i < 3; i++)
	{
		exp[i] = 0;
		level[i] = 1;
	}
}

ExpHandler::~ExpHandler()
{
}

void ExpHandler::addExp(const int e[3])
{
	for (int i=0;i<3;i++)
	{
		exp[i] += e[i];
	}
	while (isStrLevelUp())
	{
		levelStrUp();
	}
	while (isAgiLevelUp())
	{
		levelAgiUp();
	}
	while (isIntLevelUp())
	{
		levelIntUp();
	}
}


int ExpHandler::getCurStrLevel()
{
	return level[0];
}

int ExpHandler::getCurAgiLevel()
{
	return level[1];
}

int ExpHandler::getCurIntLevel()
{
	return level[2];
}

int ExpHandler::getCurStrExp()
{
	return exp[0];
}

int ExpHandler::getCurAgiExp()
{
	return exp[1];
}

int ExpHandler::getCurIntExp()
{
	return exp[2];
}

void ExpHandler::levelStrUp()
{
	exp[0] = exp[0] - expRequire[level[0] + 1];
	level[0]++;
	characterPtr->setStrength(
		characterPtr->getOriStrength() + 1
	);
}

void ExpHandler::levelAgiUp()
{
	exp[1] = exp[1] - expRequire[level[1] + 1];
	level[1]++;
	characterPtr->setAgility(
		characterPtr->getAgility() + 1
	);
}

void ExpHandler::levelIntUp()
{
	exp[2] = exp[2] - expRequire[level[2] + 1];
	level[2]++;
	characterPtr->setIntellect(
		characterPtr->getOriIntellect() + 1
	);
}

bool ExpHandler::isStrLevelUp()
{
	if (level[Str] >= 25)
	{
		return false;
	}
	if (exp[Str] >= expRequire[level[Str] + 1])
	{
		return true;
	}
	return false;
}

bool ExpHandler::isAgiLevelUp()
{
	if (level[Agi] >= 25)
	{
		return false;
	}
	if (exp[Agi] >= expRequire[level[Agi] + 1])
	{
		return true;
	}
	return false;
}

bool ExpHandler::isIntLevelUp()
{
	if (level[Int] >= 25)
	{
		return false;
	}
	if (exp[Int] >= expRequire[level[Int] + 1])
	{
		return true;
	}
	return false;
}
