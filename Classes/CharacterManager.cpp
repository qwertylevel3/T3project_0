#include "CharacterManager.h"
#include"tinyxml2\tinyxml2.h"

USING_NS_CC;


CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

void CharacterManager::init()
{
	cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("test_character.plist");

	CharacterModel* actor0Model = new CharacterModel();
	actor0Model->setName("Actor0");

	modelMap["Actor0"] = actor0Model;
}

Character * CharacterManager::getCharacter(std::string characterName)
{
	return modelMap[characterName]->makeCharacter();
}

