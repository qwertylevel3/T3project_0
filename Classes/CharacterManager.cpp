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
}

Character * CharacterManager::getCharacter(std::string characterName)
{
	return nullptr;
}
