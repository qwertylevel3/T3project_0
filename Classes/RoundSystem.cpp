#include "RoundSystem.h"
#include "Character.h"
#include "Dungeon.h"
#include "Marco.h"

using namespace Field;

RoundSystem::RoundSystem()
{
}


RoundSystem::~RoundSystem()
{
}

void RoundSystem::init()
{
	roundCount = 0;
}

void RoundSystem::loadStorey()
{
	Storey* storey=Dungeon::getInstance()->getStorey();
	std::list<Character* >& allStoreyCharacter = storey->getAllCharacter();
	for (std::list<Character*>::iterator iter = allStoreyCharacter.begin();
		iter != allStoreyCharacter.end();
		iter++)
	{
		allCharacter.push_back(*iter);
	}
}

int RoundSystem::getRoundCount()
{
	return roundCount;
}

void RoundSystem::nextRound()
{
	roundCount++;
#ifdef CONSOLE
	std::cout << "round:" <<roundCount<< std::endl;
#endif
	for each (Character*  character in allCharacter)
	{
		if (!character->isDead())
		{
			character->update();
		}
	}
}
