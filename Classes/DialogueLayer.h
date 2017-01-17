#pragma once

#include "2d/CCLayer.h"
#include "Singleton.h"

class DialogueLayer:public cocos2d::Layer,public Singleton<DialogueLayer>
{
public:
	DialogueLayer();
	~DialogueLayer();
	bool init();
};

