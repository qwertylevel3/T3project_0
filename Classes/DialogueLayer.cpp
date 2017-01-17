#include "DialogueLayer.h"
#include "DialogueSystem.h"



DialogueLayer::DialogueLayer()
{
}


DialogueLayer::~DialogueLayer()
{
}

bool DialogueLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	DialogueSystem::getInstance()->init();

	return true;
}
