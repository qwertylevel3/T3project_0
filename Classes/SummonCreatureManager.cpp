#include "SummonCreatureManager.h"
#include "Player.h"
#include "Character.h"
#include "Dungeon.h"
#include "ToolFunction.h"

SummonCreatureManager::SummonCreatureManager()
{
}

SummonCreatureManager::~SummonCreatureManager()
{
}

void SummonCreatureManager::init()
{
	for each (Character* creature in creatureList)
	{
		delete creature;
	}
}

void SummonCreatureManager::initMission()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	cocos2d::Point playerCoord = playerCharacterPtr->getMapCoord();

	for each (Character* creature in creatureList)
	{
		if (!creature->isDead())
		{
			cocos2d::Point coord = ToolFunction::findValidPlace(
				Field::Dungeon::getInstance()->getStorey(),
				playerCoord
			);
			creature->setMapCoord(coord);
			Field::Dungeon::getInstance()->addCharacter(creature);
		}
	}
}

void SummonCreatureManager::addCharacter(Character* creature)
{
	creatureList.push_back(creature);
}