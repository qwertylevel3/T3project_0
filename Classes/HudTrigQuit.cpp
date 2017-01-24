#include "HudTrigQuit.h"
#include "base/CCDirector.h"
#include "GameSaveManager.h"



HudTrigQuit::HudTrigQuit()
{
}


HudTrigQuit::~HudTrigQuit()
{
}

void HudTrigQuit::run()
{
	GameSaveManager::getInstance()->save();

	cocos2d::Director::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
