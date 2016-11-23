#include "ResourceManager.h"
#include "2d/CCSpriteFrameCache.h"


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::init()
{

}

void ResourceManager::initCharacterRes()
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character/test_character.plist");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character/vergil.plist");
}

void ResourceManager::initHudRes()
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("HUD/Bar.plist");
}

void ResourceManager::initMaskRes()
{

}
