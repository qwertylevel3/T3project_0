#pragma once

#include "Singleton.h"
#include <string>
#include "base/CCEventKeyboard.h"

class DialogueSystem:public Singleton<DialogueSystem>
{
public:
	DialogueSystem();
	~DialogueSystem();
	void init();
	void runDialogue(const std::string& dialogueName);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
};

