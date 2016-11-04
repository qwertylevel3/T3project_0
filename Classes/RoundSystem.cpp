#include "RoundSystem.h"
#include "Character.h"
#include "Dungeon.h"
#include "Marco.h"
#include "KeyController.h"
#include "Player.h"

using namespace Field;

RoundSystem::RoundSystem()
{
}


RoundSystem::~RoundSystem()
{
}

void RoundSystem::init()
{
	temp = 0;
	roundCount = 0;
}

void RoundSystem::loadStorey()
{
	int index = 0;
	Storey* storey=Dungeon::getInstance()->getStorey();
	std::list<Character* >& allStoreyCharacter = storey->getAllCharacter();
	for (std::list<Character*>::iterator iter = allStoreyCharacter.begin();
		iter != allStoreyCharacter.end();
		iter++)
	{
		allCharacter.push_back(*iter);
		//初始化加载所有character的时候，将第一个行动设为player
		if (isPlayer(*iter))
		{
			curIndex = index;
		}
		index++;
	}
}

int RoundSystem::getRoundCount()
{
	return roundCount;
}

void RoundSystem::nextRound()
{
	allCharacter[curIndex]->endRound();

	do 
	{
		nextIndex();
	} while (allCharacter[curIndex]->isDead());

	allCharacter[curIndex]->startRound();
	round(curIndex);
}

void RoundSystem::nextIndex()
{
	curIndex++;
	if (curIndex>=allCharacter.size())
	{
		curIndex = 0;
	}
}

bool RoundSystem::isPlayer(Character* character)
{
	return character == Player::getInstance()->getcharacterPtr();
}

void RoundSystem::round(int index)
{
	temp++;
	if (temp==1000)
	{
		int a = 9;
	}


	Character* curCharacter = allCharacter[index];
	curCharacter->update();

	if (isPlayer(allCharacter[index]))
	{
		KeyController::getInstance()->setBlock(false);

	}
	else
	{
		KeyController::getInstance()->setBlock(true);
		curCharacter->action();
	}

	//curCharacter->update();
}

void RoundSystem::readyForPlayerRound()
{
	Player::getInstance()->getcharacterPtr()->update();
}
